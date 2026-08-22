#!/bin/sh
# Documentation conformance.
#
# The documentation makes quantitative claims about the repository: line
# counts, a documentation-to-code ratio, exact program output, a compiler
# invocation that produces no diagnostics, and a test suite printed inline.
#
# Claims of that kind rot. This suite treats them as assertions and fails
# the build when the prose and the repository disagree.
set -u
. "$(dirname "$0")/lib.sh"

SRC="$ROOT/hello.c"
README="$ROOT/README.md"
INSTR="$ROOT/INSTRUCTIONS.md"

# Ground truth, computed from the repository rather than asserted.
TOTAL_LINES=$(wc -l < "$SRC" | tr -d ' ')
SIG_LINES=$(sed 's|/\*|\n&|g; s|\*/|&\n|g' "$SRC" \
            | awk '/\/\*/{c=1} !c && NF {print} /\*\//{c=0}' \
            | grep -c '[^[:space:]]' | tr -d ' ')
DOC_LINES=$((TOTAL_LINES - SIG_LINES))
RATIO=$(awk -v d="$DOC_LINES" -v s="$SIG_LINES" 'BEGIN{printf "%d", d/s + 0.5}')

printf '    hello.c: %s lines total, %s significant, %s commentary, ratio %s:1\n' \
    "$TOTAL_LINES" "$SIG_LINES" "$DOC_LINES" "$RATIO"

section "Quantitative claims in README.md"

# grep_claim <description> <file> <pattern>
# Claims are checked against a comma-stripped copy of the file, so that
# prose may write "2,712" while the computed ground truth is "2712".
grep_claim() {
    TESTS_RUN=$((TESTS_RUN + 1))
    if sed 's/\([0-9]\),\([0-9]\)/\1\2/g' "$2" | grep -qF "$3"; then
        TESTS_PASSED=$((TESTS_PASSED + 1))
        printf '%s  PASS%s  %s\n' "$C_PASS" "$C_OFF" "$1"
    else
        TESTS_FAILED=$((TESTS_FAILED + 1))
        FAILURES="${FAILURES}\n  - $1 (expected to find: $3)"
        printf '%s  FAIL%s  %s\n' "$C_FAIL" "$C_OFF" "$1"
        printf '        expected the file to contain: %s\n' "$3"
    fi
}

grep_claim "stated lines of code matches reality" \
    "$README" "**Lines of code:** $SIG_LINES"

grep_claim "stated in-source documentation lines matches reality" \
    "$README" "**Lines of documentation:** $DOC_LINES (in-source)"

grep_claim "stated documentation-to-code ratio matches reality" \
    "$README" "**Documentation-to-code ratio:** $RATIO:1"

grep_claim "section 1.2 states the correct total line count" \
    "$README" "is $TOTAL_LINES lines"

grep_claim "section 1.2 states the correct commentary line count" \
    "$README" "remaining $DOC_LINES"

grep_claim "section 12.5 states the correct ratio" \
    "$README" "$RATIO times the size of the program"

section "Quantitative claims in INSTRUCTIONS.md"

grep_claim "section 9.1 states the correct line count" \
    "$INSTR" "$TOTAL_LINES lines"

grep_claim "section 9.1 states the correct significant line count" \
    "$INSTR" "of which $SIG_LINES are the program"

section "Documented behaviour matches actual behaviour"

equals "README section 2 documents the actual output" \
    "Hello, World!" "$("$BIN")"

_readme_bytes=$(grep -oE 'Expected: \`14\`' "$INSTR" | head -1)
equals "INSTRUCTIONS section 14.2 documents the actual byte count" \
    "Expected: \`$("$BIN" | wc -c | tr -d ' ')\`" "$_readme_bytes"

section "Documented commands are executable"

# The README's recommended invocation must produce no diagnostics, because
# section 5.2 says so without qualification.
_log=$(mktemp)
$CC -Wall -Wextra -pedantic -std=c99 -O2 -o /dev/null "$SRC" > "$_log" 2>&1
_rc=$?
ok "README section 5.2 invocation compiles" test "$_rc" -eq 0
equals "README section 5.2 invocation emits no diagnostics" "" "$(cat "$_log")"
rm -f "$_log"

section "The inline test suite in README section 11.2"

# Extract the suite from the README and run it. If the documentation
# prints a test suite, the suite it prints must pass.
_suite=$(mktemp)
# Extracted with awk rather than sed: BSD sed does not support \| in a
# basic regular expression, and this suite must run on macOS runners.
awk '/^### 11.2 The full suite/,/^### 11.3/' "$README" \
    | awk '/^```/ { infence = !infence; next } infence' > "$_suite"

if [ -s "$_suite" ]; then
    ( cd "$ROOT" && sh "$_suite" ) > "$_suite.out" 2>&1
    _rc=$?
    ok "the suite printed in the README passes when run" test "$_rc" -eq 0
    sed 's/^/        /' "$_suite.out"
    rm -f "$_suite.out"
else
    skip "inline suite" "could not extract a fenced block from section 11.2"
fi
rm -f "$_suite"

section "Repository description"

# GitHub's description field is edited in a web form and stored outside the
# repository, which is how it drifts from the thing it describes. The
# canonical text lives in .github/description.txt so that it appears in
# diffs and can be checked here.
#
# The budget is 155 characters rather than GitHub's 350-character maximum:
# search engines truncate the displayed snippet at roughly 155, so anything
# beyond that is stored and indexed but never shown to a human deciding
# whether to click. Truncation is measured in pixels rather than characters,
# so 155 is a guide and not a guarantee.

DESCFILE="$ROOT/.github/description.txt"

if [ -f "$DESCFILE" ]; then
    _desc=$(cat "$DESCFILE")

    # Characters, not bytes. GitHub counts characters; `wc -c` counts bytes,
    # and the two diverge the moment the text contains anything non-ASCII --
    # an em dash is one character and three bytes. `wc -m` is character-aware
    # given a UTF-8 locale. Both are reported below so that a divergence is
    # visible rather than silent.
    _chars=$(printf '%s' "$_desc" | LC_ALL=en_US.UTF-8 wc -m | tr -d ' ')
    _bytes=$(printf '%s' "$_desc" | wc -c | tr -d ' ')

    printf '    description: %s characters (%s bytes); budget 155, GitHub caps at 350\n' \
        "$_chars" "$_bytes"

    # A ceiling rather than an equality. The meaningful constraint is that
    # the text survives the search-result snippet intact; pinning an exact
    # length would fail on any reasonable rewording, and would tempt whoever
    # hit it to pad the sentence rather than fix the test.
    ok "the description fits the ~155-character search snippet" \
        test "$_chars" -le 155

    # A floor as well, so the field cannot be quietly gutted to a few words
    # without anything noticing.
    ok "the description is substantial (at least 120 characters)" \
        test "$_chars" -ge 120

    ok "the description is within GitHub's 350-character limit" \
        test "$_chars" -le 350

    equals "the description is a single line" \
        "1" "$(wc -l < "$DESCFILE" | tr -d ' ')"

    # GitHub renders the field as plain text; a tab or control character
    # would be collapsed and the stored value would stop matching this file.
    equals "the description contains no tab or control characters" \
        "0" "$(printf '%s' "$_desc" | LC_ALL=C tr -dc '\000-\010\011\013-\037' | wc -c | tr -d ' ')"

    # The description deliberately quotes no counts, versions, or dates.
    # Every figure in this repository is verified somewhere, but the
    # description is the one piece of text that lives on GitHub rather than
    # in the tree, so a figure here could go stale without any commit
    # touching it. Keeping numbers out is what makes that impossible.
    equals "the description states no figure that could go stale" \
        "" "$(printf '%s' "$_desc" | grep -o '[0-9]' | tr -d '\n')"

    # The primary keyword must lead: search engines weight the opening of a
    # description, and a reader scanning results reads the first few words.
    ok "the description opens with the primary keyword" \
        sh -c "head -c 16 '$DESCFILE' | grep -q '^Hello World in C'"
else
    skip "repository description" ".github/description.txt not present"
fi

section "Section numbering"

# Numbers are cross-referenced by the documents and by the suites. A skipped
# or duplicated one breaks those references without breaking anything else.
if command -v python3 >/dev/null 2>&1; then
    python3 "$ROOT/tests/sections.py"
    ok "every numbered section is unique and none are skipped" test $? -eq 0
else
    skip "section numbering" "python3 unavailable"
fi

section "Makefile self-documentation"

# `make help` prints the file's leading comment block. An earlier version
# used a hardcoded line range and began leaking variable definitions when
# the header grew; the assertions below are what would have caught it.
_help=$( cd "$ROOT" && make help 2>/dev/null )

equals "make help emits no variable assignments" \
    "" "$(printf '%s\n' "$_help" | grep -E '^[A-Z_]+[[:space:]]*[?:]?=' || true)"

equals "make help emits no recipe lines" \
    "" "$(printf '%s\n' "$_help" | grep -E '^\t' || true)"

ok "make help lists the Targets heading" \
    sh -c "printf '%s\n' \"\$0\" | grep -q '^Targets:'" "$_help"

# Every target documented in help must exist, and every public target must
# be documented. Drift in either direction is a defect.
# Temp files rather than process substitution: <(...) is a bashism, and
# this suite runs under POSIX sh. When it was written with <(...) the
# command substitution errored, the result was empty, and both assertions
# below passed vacuously -- the precise failure mode they exist to catch.
_docf=$(mktemp); _phof=$(mktemp)
printf '%s\n' "$_help" \
    | awk '/^Targets:/ { f = 1; next } f && /^  [a-z]/ { print $1 }' \
    | sort > "$_docf"
( cd "$ROOT" && grep '^\.PHONY:' Makefile | sed 's/^\.PHONY://' ) \
    | tr ' ' '\n' | grep -v '^$' | sort -u > "$_phof"

printf '    %s documented, %s declared .PHONY\n' \
    "$(wc -l < "$_docf" | tr -d ' ')" "$(wc -l < "$_phof" | tr -d ' ')"

# Guard against both files being empty, which would make the comparisons
# below succeed without comparing anything.
ok "make help produced a non-empty target list" test -s "$_docf"
ok "the Makefile declares .PHONY targets" test -s "$_phof"

equals "every .PHONY target is documented in make help" \
    "" "$(comm -13 "$_docf" "$_phof" | tr '\n' ' ' | sed 's/ *$//')"

equals "every target in make help exists" \
    "" "$(comm -23 "$_docf" "$_phof" | tr '\n' ' ' | sed 's/ *$//')"

rm -f "$_docf" "$_phof"

section "Cross-references and links"

if command -v python3 >/dev/null 2>&1; then
    python3 "$ROOT/tests/links.py"
    ok "every link and source cross-reference resolves" test $? -eq 0
else
    skip "link checking" "python3 unavailable"
fi

section "File hygiene"

for f in "$SRC" "$README" "$INSTR" "$ROOT/Makefile" \
         "$ROOT/INSTALL.md" "$ROOT/UNINSTALL.md" "$ROOT/CONTRIBUTING.md" \
         "$ROOT/SECURITY.md" "$ROOT/SUPPORT.md" "$ROOT/CHANGELOG.md" \
         "$ROOT/CODE_OF_CONDUCT.md" "$ROOT/LICENSE" "$ROOT/CITATION.cff" \
         "$ROOT/hello.1" "$ROOT/.editorconfig" "$ROOT/.gitignore"; do
    [ -f "$f" ] || continue
    _b=$(basename "$f")
    ok "$_b ends with a newline" \
        sh -c "[ -z \"\$(tail -c1 '$f')\" ]"
    _tw=$(grep -c '[[:space:]]$' "$f" | tr -d ' ')
    equals "$_b has no trailing whitespace" "0" "$_tw"
done

section "Comment integrity"

# C block comments do not nest. A stray sequence inside the dissertation
# would silently truncate 2,700 lines of commentary and, worse, might
# still compile.
_opens=$(grep -c '/\*' "$SRC" | tr -d ' ')
_closes=$(grep -c '\*/' "$SRC" | tr -d ' ')
equals "block comment delimiters are balanced" "$_opens" "$_closes"

ok "no nested comment openers" \
    sh -c "! sed -n '/\\/\\*/,/\\*\\//{ /\\/\\*/{ x; /./{ x; p; d }; x; h }; /\\*\\//{ s/.*//; h } }' '$SRC' | grep -q ."

section "Source is pure ASCII"

# README section 10.4 discusses EBCDIC portability; a non-ASCII byte in
# the source would undermine the claim and can break older toolchains.
_nonascii=$(LC_ALL=C grep -c '[^\t -~]' "$SRC" | tr -d ' ')
equals "hello.c contains no non-ASCII bytes" "0" "$_nonascii"

summary
