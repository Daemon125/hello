#!/bin/sh
# Repository hygiene.
#
# Verifies that .gitignore excludes every artifact the build is capable of
# producing, and that it excludes nothing the repository needs.
#
# The exclusion checks run against a scratch repository containing only
# this project's .gitignore, so that the patterns themselves are tested
# rather than the state of whatever tree the suite happens to be run in.
# Checks that genuinely require the real repository -- what is tracked,
# and with which file mode -- run only when there is one, and are skipped
# otherwise.
set -u
. "$(dirname "$0")/lib.sh"

if ! command -v git >/dev/null 2>&1; then
    skip "repository hygiene" "git not installed"
    summary
    exit 0
fi

if [ ! -f "$ROOT/.gitignore" ]; then
    printf '%s  FAIL%s  .gitignore is missing\n' "$C_FAIL" "$C_OFF"
    exit 1
fi

# --------------------------------------------------------------- scratch

SCRATCH=$(mktemp -d)
trap 'rm -rf "$SCRATCH"' EXIT INT TERM
cp "$ROOT/.gitignore" "$SCRATCH/"
( cd "$SCRATCH" && git init -q -b master . ) 2>/dev/null \
    || ( cd "$SCRATCH" && git init -q . )

# materialize <path> [dir]
#
# git check-ignore resolves most patterns from the path string alone, but a
# directory-only pattern (one with a trailing slash, such as *.dSYM/) matches
# only if the path is a directory on disk. Paths are therefore created, but
# never overwritten: an earlier version of this helper truncated whatever it
# touched, and since one of the paths under test is .gitignore itself, it
# silently emptied the file it was testing and every subsequent assertion
# checked against nothing. The dynamic section below is what caught it.
materialize() {
    ( cd "$SCRATCH" || exit
      [ -e "$1" ] && exit 0
      case "$1" in
          .gitignore) exit 0 ;;              # never touch the file under test
          */*) mkdir -p "$(dirname "$1")" 2>/dev/null ;;
      esac
      if [ "${2:-file}" = "dir" ]; then
          mkdir -p "$1" 2>/dev/null
      else
          : > "$1" 2>/dev/null
      fi
      exit 0 )
}

# ignored <path> [dir]  -- assert the scratch .gitignore excludes <path>
ignored() {
    TESTS_RUN=$((TESTS_RUN + 1))
    materialize "$1" "${2:-file}"
    if ( cd "$SCRATCH" && git check-ignore -q "$1" ); then
        TESTS_PASSED=$((TESTS_PASSED + 1))
        printf '%s  PASS%s  ignored: %s\n' "$C_PASS" "$C_OFF" "$1"
    else
        TESTS_FAILED=$((TESTS_FAILED + 1))
        FAILURES="${FAILURES}\n  - .gitignore does not exclude $1"
        printf '%s  FAIL%s  NOT ignored: %s\n' "$C_FAIL" "$C_OFF" "$1"
    fi
}

# kept <path>   -- assert the scratch .gitignore does NOT exclude <path>
kept() {
    TESTS_RUN=$((TESTS_RUN + 1))
    materialize "$1"
    if ( cd "$SCRATCH" && git check-ignore -q "$1" ); then
        TESTS_FAILED=$((TESTS_FAILED + 1))
        FAILURES="${FAILURES}\n  - .gitignore wrongly excludes $1"
        printf '%s  FAIL%s  wrongly ignored: %s\n' "$C_FAIL" "$C_OFF" "$1"
    else
        TESTS_PASSED=$((TESTS_PASSED + 1))
        printf '%s  PASS%s  tracked: %s\n' "$C_PASS" "$C_OFF" "$1"
    fi
}

section "Build products are excluded"

# Every artifact named by a -o flag, a tee, or a rm -f in the Makefile or
# in .github/workflows/ci.yml. If a build rule gains a new output and this
# list is not updated, the next section catches it.
for a in hello hello.exe hello-static hello-asan hello-san hello-tcc \
         hello-c89 hello-c++98 hello-c++20 \
         hello-aarch64 hello-armhf hello-riscv64 hello-powerpc64le \
         hello-s390x-big-endian \
         repro first.txt second.txt build.log \
         hello.o hello.i hello.s a.out hello-src.tar.gz
do
    ignored "$a"
done

section "Toolchain and editor artifacts are excluded"

ignored "hello.dSYM" dir

for a in hello.dSYM/Contents/Info.plist hello.pdb hello.gcda hello.gcno \
         default.profraw core core.1234 vgcore.99 \
         .DS_Store ._resourcefork Thumbs.db \
         .vscode/settings.json .idea/workspace.xml \
         hello.c.swp backup~ '#autosave#' hello.c.save
do
    ignored "$a"
done

section "Nothing the repository needs is excluded"

for a in hello.c README.md INSTRUCTIONS.md Makefile .gitignore \
         tests/lib.sh tests/run.sh tests/links.py tests/01-behavior.sh \
         .github/dependabot.yml .github/workflows/ci.yml \
         .github/workflows/codeql.yml .github/workflows/nightly.yml \
         .github/PULL_REQUEST_TEMPLATE.md \
         .github/ISSUE_TEMPLATE/bug_report.yml
do
    kept "$a"
done

section "Every actual build product is covered"

# Rather than trusting the list above, build for real and check whatever
# appears. This is what catches a new artifact added to the Makefile
# without a corresponding .gitignore entry.
BEFORE="$SCRATCH/before"
AFTER="$SCRATCH/after"
( cd "$ROOT" && ls -A ) | sort > "$BEFORE"
( cd "$ROOT" && make all > /dev/null 2>&1 && make sanitize > /dev/null 2>&1 ) || true
( cd "$ROOT" && ls -A ) | sort > "$AFTER"

NEW=$(comm -13 "$BEFORE" "$AFTER")
if [ -z "$NEW" ]; then
    skip "newly created artifacts" "build produced nothing new (already built)"
else
    for f in $NEW; do
        if [ -d "$ROOT/$f" ]; then
            ignored "$f" dir
        else
            ignored "$f"
        fi
    done
fi

section "Documented pattern count"

# README section 11.9 states how many build-product patterns .gitignore
# carries. Like every other figure in the documentation, it is computed
# from the file rather than trusted. See tests/05-docs.sh.
_patterns=$(sed -n '/^#  2\. THIS PROJECT/,/^#  3\. TOOLCHAIN/p' "$ROOT/.gitignore" \
            | grep -vcE '^#|^$' | tr -d ' ')
printf '    .gitignore section 2 carries %s patterns\n' "$_patterns"
equals "README section 11.9 states the correct pattern count" \
    "1" "$(grep -c "$_patterns patterns, from" "$ROOT/README.md" | tr -d ' ')"

section "Working tree state"

if ( cd "$ROOT" && git rev-parse --git-dir >/dev/null 2>&1 ); then

    # A tracked executable would defeat the entire point of the file.
    _tracked_bin=$( cd "$ROOT" && git ls-files -z 2>/dev/null \
        | xargs -0 file 2>/dev/null \
        | grep -iE 'ELF |Mach-O|PE32' | cut -d: -f1 | tr '\n' ' ' )
    equals "no compiled binary is tracked" "" "$_tracked_bin"

    # Git records the executable bit. A suite committed 100644 fails in CI
    # with "permission denied" and the cause is invisible in a diff.
    _bad_mode=$( cd "$ROOT" && git ls-files -s tests/ 2>/dev/null \
        | awk '$1 != "100755" && $4 ~ /\.sh$/ { print $4 }' | tr '\n' ' ' )
    equals "every test script is tracked as executable" "" "$_bad_mode"

    # Nothing generated should be sitting in the index.
    _dirty=$( cd "$ROOT" && git status --porcelain --ignored=no 2>/dev/null \
        | grep -E '^\?\? (hello|repro|a\.out|build\.log)' | tr '\n' ' ' )
    equals "no untracked build product is visible to git" "" "$_dirty"

else
    skip "tracked-file checks" "not inside a git repository"
fi

summary
