#!/bin/sh
# Project documentation and packaging.
#
# GitHub renders a "Community Standards" checklist for every repository and
# reports which of seven expected files are missing. This suite asserts all
# seven are present, plus the files GitHub uses for citation metadata and
# code ownership.
#
# It then verifies the claims those documents make: that the manual page
# lints, that installation places exactly the five files UNINSTALL.md
# section 6 enumerates, that the installed binary passes the behaviour
# suite, and that uninstalling removes all of it.
set -u
. "$(dirname "$0")/lib.sh"

section "GitHub community standards"

# exists <file> <why>
exists() {
    TESTS_RUN=$((TESTS_RUN + 1))
    if [ -s "$ROOT/$1" ]; then
        TESTS_PASSED=$((TESTS_PASSED + 1))
        printf '%s  PASS%s  %-22s %s\n' "$C_PASS" "$C_OFF" "$1" "$2"
    else
        TESTS_FAILED=$((TESTS_FAILED + 1))
        FAILURES="${FAILURES}\n  - missing or empty: $1 ($2)"
        printf '%s  FAIL%s  %-22s %s\n' "$C_FAIL" "$C_OFF" "$1" "$2"
    fi
}

exists README.md                         "project overview"
exists LICENSE                           "required for reuse"
exists CONTRIBUTING.md                   "linked from the PR form"
exists CODE_OF_CONDUCT.md                "linked from the community profile"
exists SECURITY.md                       "linked from the Security tab"
exists .github/PULL_REQUEST_TEMPLATE.md  "pre-fills the PR body"
exists .github/ISSUE_TEMPLATE/bug_report.yml "issue form"

section "Additional project files"

exists CHANGELOG.md          "Keep a Changelog format"
exists SUPPORT.md            "linked from the issue chooser"
exists INSTALL.md            "installation"
exists UNINSTALL.md          "removal"
exists CITATION.cff          "renders the Cite this repository control"
exists .editorconfig         "editor configuration"
exists .gitignore            "build-product exclusions"
exists .github/CODEOWNERS    "review routing"
exists .github/dependabot.yml "the pipeline's own dependencies"
exists .github/description.txt "the GitHub description, version-controlled"
exists hello.1               "manual page"
exists Makefile              "verification targets"

section "No unresolved placeholders"

# Templates ship with OWNER/REPO and @OWNER standing in for the real
# repository. Left in place they produce broken badges, 404 links, and a
# CODEOWNERS file that assigns review to nobody -- none of which fails a
# build, and all of which is visible on the repository's front page.
_ph=$( cd "$ROOT" && grep -rl 'OWNER/REPO\|@OWNER\b' \
        --include='*.md' --include='*.yml' --include='*.cff' \
        --include='CODEOWNERS' . 2>/dev/null | tr '\n' ' ' )
equals "no file contains an unresolved OWNER/REPO placeholder" "" "$_ph"

_ex=$( cd "$ROOT" && grep -rln 'example\.invalid' --include='*.yml' \
        --include='*.cff' . 2>/dev/null | tr '\n' ' ' )
equals "no shipped metadata uses a placeholder address" "" "$_ex"

section "Version consistency"

# Every file that states a version must agree. Disagreement is invisible
# until someone reads the manual page of a release and finds it claims to
# be the previous one. CITATION.cff is the source of truth because it is
# the only machine-readable declaration.
_ver=$(sed -n 's/^version: *//p' "$ROOT/CITATION.cff" | head -1)
printf '    declared version: %s (from CITATION.cff)\n' "$_ver"

ok "CITATION.cff declares a version" test -n "$_ver"

ok "the manual page states the same version" \
    grep -q "\"hello $_ver\"" "$ROOT/hello.1"

ok "CHANGELOG.md has an entry for this version" \
    grep -q "^## \[$_ver\]" "$ROOT/CHANGELOG.md"

ok "README.md's changelog summary lists this version" \
    grep -q "^### \[$_ver\]" "$ROOT/README.md"

ok "the packaging examples in INSTALL.md use this version" \
    grep -q "Version: *$_ver" "$ROOT/INSTALL.md"

section "Metadata is machine-readable"

if command -v python3 >/dev/null 2>&1; then
    ok "CITATION.cff parses as YAML and declares cff-version 1.2.0" \
        python3 -c "
import yaml,sys
d=yaml.safe_load(open('$ROOT/CITATION.cff'))
sys.exit(0 if d.get('cff-version')=='1.2.0' and d.get('title') and d.get('references') else 1)"
else
    skip "CITATION.cff" "python3 unavailable"
fi

# The Unlicense is what README section 18 and CITATION.cff both claim.
ok "LICENSE contains a recognised public-domain dedication" \
    grep -q "released into the public domain" "$ROOT/LICENSE"

equals "CITATION.cff license matches LICENSE" \
    "1" "$(grep -c '^license: Unlicense' "$ROOT/CITATION.cff" | tr -d ' ')"

section "Manual page"

if command -v mandoc >/dev/null 2>&1; then
    _lint=$(mandoc -Tlint "$ROOT/hello.1" 2>&1)
    equals "hello.1 lints clean under mandoc" "" "$_lint"
else
    skip "mandoc lint" "mandoc not installed"
fi

ok "hello.1 declares section 1" \
    grep -q '^\.TH HELLO 1' "$ROOT/hello.1"

ok "hello.1 has the mandatory NAME section" \
    grep -q '^\.SH NAME' "$ROOT/hello.1"

if command -v man >/dev/null 2>&1; then
    ok "hello.1 renders without error" \
        sh -c "man '$ROOT/hello.1' > /dev/null 2>&1"
else
    skip "man rendering" "man unavailable"
fi

section "Install and uninstall round-trip"

# UNINSTALL.md section 6 states that installation places exactly five files
# and that there is no sixth. That is a falsifiable claim; this is the test.
STAGE=$(mktemp -d)
trap 'rm -rf "$STAGE"' EXIT INT TERM

if ( cd "$ROOT" && make install DESTDIR="$STAGE" PREFIX=/usr >/dev/null 2>&1 ); then

    _n=$(find "$STAGE" -type f | wc -l | tr -d ' ')
    equals "install places exactly 5 files (UNINSTALL.md section 6)" "5" "$_n"

    ok "the binary is installed executable" \
        test -x "$STAGE/usr/bin/hello"

    equals "the installed binary produces the specified output" \
        "Hello, World!" "$("$STAGE/usr/bin/hello" 2>/dev/null)"

    ok "the manual page is installed" \
        test -f "$STAGE/usr/share/man/man1/hello.1"

    ok "the licence is installed alongside the documentation" \
        test -f "$STAGE/usr/share/doc/hello/LICENSE"

    # The GNU-standard installcheck target verifies an installation rather
    # than a build tree.
    ok "make installcheck passes against the staged install" \
        sh -c "cd '$ROOT' && make installcheck DESTDIR='$STAGE' PREFIX=/usr >/dev/null 2>&1"

    # The installed binary, not ./hello, must satisfy the behaviour suite.
    ok "the installed binary passes the behaviour suite" \
        sh -c "BIN='$STAGE/usr/bin/hello' sh '$ROOT/tests/01-behavior.sh' >/dev/null 2>&1"

    ( cd "$ROOT" && make uninstall DESTDIR="$STAGE" PREFIX=/usr >/dev/null 2>&1 )

    _left=$(find "$STAGE" -type f | wc -l | tr -d ' ')
    equals "uninstall removes every installed file" "0" "$_left"

    ok "uninstall removes the documentation directory" \
        sh -c "! test -d '$STAGE/usr/share/doc/hello'"

    # An uninstall target that recursively deletes a directory it does not
    # exclusively own is a latent disaster. UNINSTALL.md section 2.1 claims
    # this one does not; verify by planting a foreign file.
    ( cd "$ROOT" && make install DESTDIR="$STAGE" PREFIX=/usr >/dev/null 2>&1 )
    : > "$STAGE/usr/share/doc/hello/NOT-OURS"
    ( cd "$ROOT" && make uninstall DESTDIR="$STAGE" PREFIX=/usr >/dev/null 2>&1 )
    ok "uninstall does not delete files it did not install" \
        test -f "$STAGE/usr/share/doc/hello/NOT-OURS"

else
    skip "install round-trip" "make install failed on this platform"
fi

section "Cross-document consistency"

# Every document should point back to the index, and the index should know
# about every document.
for doc in INSTALL.md UNINSTALL.md CONTRIBUTING.md SECURITY.md SUPPORT.md \
           CHANGELOG.md CODE_OF_CONDUCT.md; do
    TESTS_RUN=$((TESTS_RUN + 1))
    if grep -qF "$doc" "$ROOT/README.md"; then
        TESTS_PASSED=$((TESTS_PASSED + 1))
        printf '%s  PASS%s  README.md links %s\n' "$C_PASS" "$C_OFF" "$doc"
    else
        TESTS_FAILED=$((TESTS_FAILED + 1))
        FAILURES="${FAILURES}\n  - README.md does not link $doc"
        printf '%s  FAIL%s  README.md links %s\n' "$C_FAIL" "$C_OFF" "$doc"
    fi
done

summary
