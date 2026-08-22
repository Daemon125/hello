#!/bin/sh
# Shared assertion helpers for the hello test suite.
#
# POSIX sh only. No bashisms, no external dependencies beyond coreutils.
# The suite must run on any platform the program itself builds on, which
# per README section 10.1 includes systems where bash is not installed.

TESTS_RUN=0
TESTS_PASSED=0
TESTS_FAILED=0
FAILURES=""

# Terminal colours, suppressed when stdout is not a terminal or when
# NO_COLOR is set. See https://no-color.org/
if [ -t 1 ] && [ -z "${NO_COLOR:-}" ]; then
    C_PASS=$(printf '\033[32m'); C_FAIL=$(printf '\033[31m')
    C_DIM=$(printf '\033[2m');  C_OFF=$(printf '\033[0m')
else
    C_PASS=''; C_FAIL=''; C_DIM=''; C_OFF=''
fi

section() {
    printf '\n%s== %s ==%s\n' "$C_DIM" "$1" "$C_OFF"
}

# ok <description> <command...>
# Passes if the command exits 0.
ok() {
    _desc=$1; shift
    TESTS_RUN=$((TESTS_RUN + 1))
    if "$@" >/dev/null 2>&1; then
        TESTS_PASSED=$((TESTS_PASSED + 1))
        printf '%s  PASS%s  %s\n' "$C_PASS" "$C_OFF" "$_desc"
    else
        TESTS_FAILED=$((TESTS_FAILED + 1))
        FAILURES="${FAILURES}\n  - ${_desc}"
        printf '%s  FAIL%s  %s\n' "$C_FAIL" "$C_OFF" "$_desc"
    fi
}

# equals <description> <expected> <actual>
equals() {
    _desc=$1; _want=$2; _got=$3
    TESTS_RUN=$((TESTS_RUN + 1))
    if [ "$_want" = "$_got" ]; then
        TESTS_PASSED=$((TESTS_PASSED + 1))
        printf '%s  PASS%s  %s\n' "$C_PASS" "$C_OFF" "$_desc"
    else
        TESTS_FAILED=$((TESTS_FAILED + 1))
        FAILURES="${FAILURES}\n  - ${_desc}\n      expected: ${_want}\n      actual:   ${_got}"
        printf '%s  FAIL%s  %s\n' "$C_FAIL" "$C_OFF" "$_desc"
        printf '        expected: %s\n' "$_want"
        printf '        actual:   %s\n' "$_got"
    fi
}

# skip <description> <reason>
skip() {
    printf '%s  SKIP  %s (%s)%s\n' "$C_DIM" "$1" "$2" "$C_OFF"
}

summary() {
    printf '\n'
    if [ "$TESTS_FAILED" -eq 0 ]; then
        printf '%sPASS%s  %d assertions, 0 failures\n' \
            "$C_PASS" "$C_OFF" "$TESTS_RUN"
        return 0
    else
        # %b rather than %s: FAILURES accumulates literal \n sequences as it
        # is built up, and %s would print them as backslash-n.
        printf '%sFAIL%s  %d assertions, %d failures:' \
            "$C_FAIL" "$C_OFF" "$TESTS_RUN" "$TESTS_FAILED"
        printf '%b\n' "$FAILURES"
        return 1
    fi
}

# Resolve the repository root regardless of where the suite is invoked from.
ROOT=$(CDPATH='' cd -- "$(dirname -- "$0")/.." && pwd)
BIN="${BIN:-$ROOT/hello}"
CC="${CC:-cc}"
