#!/bin/sh
# Binary and build-artifact analysis.
#
# Verifies properties of the compiled output rather than its behaviour:
# the string is where README section 18.3 says it is, the program allocates
# nothing, links nothing beyond libc, and builds reproducibly.
set -u
. "$(dirname "$0")/lib.sh"

WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT INT TERM
SRC="$ROOT/hello.c"

section "The string literal"

# README section 18.3: fourteen bytes plus a NUL terminator, in read-only
# data. If the string is not in the binary, something has gone very wrong.
ok "the literal is present in the binary" \
    sh -c "LC_ALL=C grep -q 'Hello, World!' '$BIN'"

if command -v strings >/dev/null 2>&1; then
    equals "the literal appears exactly once" \
        "1" "$(strings "$BIN" | grep -c '^Hello, World!$' | tr -d ' ')"
else
    skip "literal occurrence count" "strings(1) unavailable"
fi

section "Section placement"

if command -v size >/dev/null 2>&1; then
    size "$BIN" | sed 's/^/    /'
    ok "size(1) reports a valid object" size "$BIN"
else
    skip "section sizes" "size(1) unavailable"
fi

# The string must be read-only. A writable copy would mean the compiler
# had placed it in .data, which would be legal and wrong.
if command -v objdump >/dev/null 2>&1; then
    ok "a read-only data section exists" \
        sh -c "objdump -h '$BIN' 2>/dev/null | grep -qE '__cstring|\\.rodata|__TEXT'"
elif command -v otool >/dev/null 2>&1; then
    ok "a read-only cstring section exists" \
        sh -c "otool -l '$BIN' 2>/dev/null | grep -q '__cstring'"
else
    skip "read-only placement" "no object inspector available"
fi

section "Linkage"

# README section 9.5: one dependency. Anything else in this list is a
# supply chain the project does not claim to have.
if command -v ldd >/dev/null 2>&1; then
    ldd "$BIN" 2>/dev/null | sed 's/^/    /'
    _n=$(ldd "$BIN" 2>/dev/null | grep -cE '=>' | tr -d ' ')
    ok "no more than three shared objects (libc + loader)" test "$_n" -le 3
elif command -v otool >/dev/null 2>&1; then
    otool -L "$BIN" | sed 's/^/    /'
    _n=$(otool -L "$BIN" | tail -n +2 | wc -l | tr -d ' ')
    equals "exactly one shared library (libSystem)" "1" "$_n"
else
    skip "linkage inspection" "no linker inspector available"
fi

section "Symbols"

# The program defines exactly one function of its own and imports exactly
# one. An unexpected import means the compiler substituted something.
if command -v nm >/dev/null 2>&1; then
    _undef=$(nm -u "$BIN" 2>/dev/null | grep -oE '_?(printf|puts)' | sort -u | tr '\n' ' ')
    printf '    imported output function: %s\n' "${_undef:-none visible}"
    ok "main is defined" sh -c "nm '$BIN' 2>/dev/null | grep -qE ' T _?main'"
else
    skip "symbol table" "nm(1) unavailable"
fi

section "Heap allocation"

# README section 8.3 claims zero bytes allocated by the program. The
# stdout buffer is allocated by libc on its behalf and is not counted.
if command -v valgrind >/dev/null 2>&1; then
    valgrind --error-exitcode=99 --leak-check=full --errors-for-leak-kinds=all \
             "$BIN" > "$WORK/vg.out" 2> "$WORK/vg.err"
    _vg=$?
    ok "valgrind reports no errors and no leaks" test "$_vg" -ne 99
    equals "output under valgrind is unchanged" \
        "Hello, World!" "$(cat "$WORK/vg.out")"
else
    skip "valgrind" "not installed"
fi

section "Reproducibility"

# Reproducibility is tested by building twice to the *same* output path.
#
# Building to two different paths and comparing is a common and incorrect
# formulation of this test: many toolchains embed the output filename in
# the image (Apple's linker records it in the debug map for dSYM lookup),
# so the images differ by the name alone and the test reports
# nondeterminism that does not exist. Building twice to one path and
# copying the first result aside removes that variable.

$CC -std=c99 -O2 -c -o "$WORK/obj.o" "$SRC" 2>/dev/null
cp "$WORK/obj.o" "$WORK/obj-first.o"
$CC -std=c99 -O2 -c -o "$WORK/obj.o" "$SRC" 2>/dev/null
equals "compiler output is byte-identical across builds" \
    "$(cksum < "$WORK/obj-first.o")" "$(cksum < "$WORK/obj.o")"

# The linked image additionally carries a build identifier on most
# platforms -- LC_UUID from Apple's ld64, .note.gnu.build-id from GNU ld --
# which is derived from content but emitted fresh per link. Suppress it
# where the linker allows.
LDREPRO=''
if $CC -std=c99 -Wl,-no_uuid -o "$WORK/probe" "$SRC" 2>/dev/null; then
    LDREPRO='-Wl,-no_uuid'
elif $CC -std=c99 -Wl,--build-id=none -o "$WORK/probe" "$SRC" 2>/dev/null; then
    LDREPRO='-Wl,--build-id=none'
fi

$CC -std=c99 -O2 $LDREPRO -o "$WORK/img" "$SRC" 2>/dev/null
cp "$WORK/img" "$WORK/img-first"
$CC -std=c99 -O2 $LDREPRO -o "$WORK/img" "$SRC" 2>/dev/null
equals "linked image is byte-identical across builds${LDREPRO:+ ($LDREPRO)}" \
    "$(cksum < "$WORK/img-first")" "$(cksum < "$WORK/img")"

section "Optimization invariance"

# Every optimization level must produce the same observable behaviour.
# README section 5.6 notes there is nothing here to optimize; this asserts
# the compiler agrees.
for opt in -O0 -O1 -O2 -O3 -Os; do
    $CC -std=c99 "$opt" -o "$WORK/o" "$SRC" 2>/dev/null
    equals "output identical at $opt" "Hello, World!" "$("$WORK/o")"
done

section "Static linking"

if $CC -static -std=c99 -o "$WORK/static" "$SRC" 2>/dev/null; then
    equals "statically linked binary behaves identically" \
        "Hello, World!" "$("$WORK/static")"
    _dyn=$(wc -c < "$BIN" | tr -d ' ')
    _sta=$(wc -c < "$WORK/static" | tr -d ' ')
    printf '    dynamic: %s bytes    static: %s bytes\n' "$_dyn" "$_sta"
    ok "static binary is larger than dynamic" test "$_sta" -gt "$_dyn"
else
    skip "static linking" "not supported on this platform"
fi

section "Intermediate stages"

# INSTRUCTIONS section 12.6 tells the reader they can inspect each stage.
# These assertions verify that the instructions given are accurate.
$CC -E "$SRC" > "$WORK/pp.i" 2>/dev/null
_pp=$(wc -l < "$WORK/pp.i" | tr -d ' ')
printf '    preprocessed: %s lines\n' "$_pp"
ok "preprocessor output is substantially larger than the source" \
    test "$_pp" -gt 100

ok "preprocessor strips every comment" \
    sh -c "! grep -q 'Proto-Indo-European' '$WORK/pp.i'"

$CC -S -std=c99 -O0 -o "$WORK/hello.s" "$SRC" 2>/dev/null
ok "compiler emits assembly" test -s "$WORK/hello.s"
ok "assembly contains the string literal" \
    sh -c "LC_ALL=C grep -q 'Hello, World' '$WORK/hello.s'"

_asm=$(grep -cE '^\s+[a-z]' "$WORK/hello.s" | tr -d ' ')
printf '    assembly: %s instruction-ish lines at -O0\n' "$_asm"

summary
