#!/bin/sh
# Standards conformance.
#
# README section 5.4 claims the program builds clean under every C standard
# from C89 to C23, and additionally as C++. This suite is the evidence.
#
# Every build here uses -Werror. A warning is a failure; the README makes an
# unqualified claim of zero diagnostics and the suite holds it to that.
set -u
. "$(dirname "$0")/lib.sh"

WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT INT TERM

SRC="$ROOT/hello.c"
WARN="-Wall -Wextra -pedantic -Werror"

# build_clean <label> <extra flags...>
# Compiles, asserts no diagnostics were emitted, and asserts the resulting
# binary produces the specified output.
build_clean() {
    _label=$1; shift
    _out="$WORK/h$$"
    _log="$WORK/log$$"
    TESTS_RUN=$((TESTS_RUN + 1))

    if ! $CC "$@" -o "$_out" "$SRC" > "$_log" 2>&1; then
        TESTS_FAILED=$((TESTS_FAILED + 1))
        FAILURES="${FAILURES}\n  - ${_label}: compilation failed"
        printf '%s  FAIL%s  %s (did not compile)\n' "$C_FAIL" "$C_OFF" "$_label"
        sed 's/^/        /' "$_log"
        return 1
    fi
    if [ -s "$_log" ]; then
        TESTS_FAILED=$((TESTS_FAILED + 1))
        FAILURES="${FAILURES}\n  - ${_label}: emitted diagnostics"
        printf '%s  FAIL%s  %s (emitted diagnostics)\n' "$C_FAIL" "$C_OFF" "$_label"
        sed 's/^/        /' "$_log"
        return 1
    fi
    if [ "$("$_out")" != "Hello, World!" ]; then
        TESTS_FAILED=$((TESTS_FAILED + 1))
        FAILURES="${FAILURES}\n  - ${_label}: wrong output"
        printf '%s  FAIL%s  %s (wrong output)\n' "$C_FAIL" "$C_OFF" "$_label"
        return 1
    fi
    TESTS_PASSED=$((TESTS_PASSED + 1))
    printf '%s  PASS%s  %s\n' "$C_PASS" "$C_OFF" "$_label"
    rm -f "$_out" "$_log"
}

# supports <flag> -- does this compiler accept the flag at all?
supports() {
    $CC "$1" -E -xc /dev/null >/dev/null 2>&1
}

printf 'compiler: %s\n' "$($CC --version 2>&1 | head -1)"

section "Language standards"

for std in c89 c90 c99 c11 c17 c18 c2x c23; do
    if supports "-std=$std"; then
        build_clean "-std=$std" -std=$std $WARN
    else
        skip "-std=$std" "not supported by this compiler"
    fi
done

section "GNU dialects"

for std in gnu89 gnu99 gnu11 gnu17; do
    if supports "-std=$std"; then
        build_clean "-std=$std" -std=$std $WARN
    else
        skip "-std=$std" "not supported by this compiler"
    fi
done

section "Optimization levels"

for opt in -O0 -O1 -O2 -O3 -Os -Og; do
    if supports "$opt"; then
        build_clean "$opt" -std=c99 $WARN "$opt"
    else
        skip "$opt" "not supported by this compiler"
    fi
done

section "Hardening flags"

for flag in \
    "-fstack-protector-strong" \
    "-D_FORTIFY_SOURCE=2 -O2" \
    "-fPIE" \
    "-fno-common" \
    "-ftrapv" \
    "-fno-strict-aliasing"
do
    _f=$(echo "$flag" | awk '{print $1}')
    if supports "$_f"; then
        build_clean "$flag" -std=c99 $WARN $flag
    else
        skip "$flag" "not supported by this compiler"
    fi
done

section "Additional diagnostics"

# Flags beyond -Wall -Wextra that catch real classes of defect. The
# format-security pair is the one that matters: it is what would fire if
# the format string were not a literal. See README section 9.2.
for w in \
    -Wformat=2 \
    -Wformat-security \
    -Wformat-nonliteral \
    -Wconversion \
    -Wsign-conversion \
    -Wshadow \
    -Wcast-qual \
    -Wwrite-strings \
    -Wstrict-prototypes \
    -Wmissing-prototypes \
    -Wold-style-definition \
    -Wredundant-decls \
    -Wundef \
    -Wvla \
    -Wdouble-promotion
do
    if supports "$w"; then
        build_clean "$w" -std=c99 $WARN "$w"
    else
        skip "$w" "not supported by this compiler"
    fi
done

section "Maximal pedantry"

# Everything at once. If this passes there is no diagnostic the compiler
# knows how to emit that this program triggers.
if supports -Weverything; then
    # Four suppressions, each justified:
    #   declaration-after-statement  - a C89 style rule; irrelevant here
    #   unsafe-buffer-usage          - flags all pointer arithmetic in libc headers
    #   pre-c11-compat / c99-compat  - warn that the code is NOT older than it is
    #   poison-system-directories    - a property of the host include path,
    #                                  not of this source file
    build_clean "-Weverything (clang)" -std=c99 -Werror -Weverything \
        -Wno-declaration-after-statement -Wno-unsafe-buffer-usage \
        -Wno-pre-c11-compat -Wno-c99-compat -Wno-poison-system-directories
else
    skip "-Weverything" "clang only"
fi

section "C++ compatibility"

# README section 5.4 claims the file is valid C++ unmodified. C++ has no
# implicit conversion from void* and stricter rules throughout, so this is
# a real check rather than a formality.
for cxx in c++98 c++11 c++17 c++20; do
    if command -v c++ >/dev/null 2>&1; then
        _out="$WORK/cxx$$"
        TESTS_RUN=$((TESTS_RUN + 1))
        if c++ -std=$cxx -Wall -Wextra -pedantic -Werror \
               -x c++ -o "$_out" "$SRC" >/dev/null 2>&1 \
           && [ "$("$_out")" = "Hello, World!" ]; then
            TESTS_PASSED=$((TESTS_PASSED + 1))
            printf '%s  PASS%s  builds and runs as %s\n' "$C_PASS" "$C_OFF" "$cxx"
        else
            TESTS_FAILED=$((TESTS_FAILED + 1))
            FAILURES="${FAILURES}\n  - $cxx"
            printf '%s  FAIL%s  builds and runs as %s\n' "$C_FAIL" "$C_OFF" "$cxx"
        fi
        rm -f "$_out"
    else
        skip "$cxx" "no C++ compiler"
    fi
done

summary
