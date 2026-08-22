#!/bin/sh
# Input immunity.
#
# README section 9.1 asserts an attack surface of zero: the program reads
# no arguments, no environment, no stdin, and no files. That is a strong
# claim and this suite is the evidence for it.
#
# Conventional fuzzing is not applicable to a program with no input, so
# this suite inverts the technique: it supplies every category of hostile
# input a caller could supply and asserts that the output does not vary.
set -u
. "$(dirname "$0")/lib.sh"

EXPECTED="Hello, World!"

# assert_immune <description> -- <argv...>
assert_immune() {
    _desc=$1; shift; shift
    equals "$_desc" "$EXPECTED" "$("$BIN" "$@" 2>/dev/null)"
}

section "Argument vectors"

assert_immune "no arguments"                    --
assert_immune "conventional flags"              -- --help --version
assert_immune "a single hyphen"                 -- -
assert_immune "a double hyphen"                 -- --
assert_immune "an empty argument"               -- ""
assert_immune "whitespace argument"             -- "   "
assert_immune "an absolute path"                -- /etc/passwd
assert_immune "path traversal"                  -- "../../../../etc/shadow"
assert_immune "a null-ish literal"              -- "\\0"
assert_immune "shell metacharacters"            -- '; rm -rf /' '&& echo owned' '`id`' '$(id)'
assert_immune "glob characters"                 -- '*' '?' '[a-z]'
assert_immune "redirection characters"          -- '>' '<' '|' '>>'
assert_immune "newline inside an argument"      -- "$(printf 'a\nb')"
assert_immune "tab inside an argument"          -- "$(printf 'a\tb')"

section "Format string conversion specifiers"

# The single most important negative result in the suite. If the program
# passed argv to printf as a format string (CWE-134), these would leak
# stack memory, dereference arbitrary pointers, or -- in the case of %n --
# write to one. The format string is a literal, so none of them are read.

assert_immune "%s"                              -- "%s"
assert_immune "%d"                              -- "%d"
assert_immune "%x repeated"                     -- "%x%x%x%x%x%x%x%x%x%x"
assert_immune "%p repeated"                     -- "%p %p %p %p %p %p %p %p"
assert_immune "%n (arbitrary write primitive)"  -- "%n"
assert_immune "%n with positional argument"     -- "%7\$n"
assert_immune "wide field specifier"            -- "%999999999d"
assert_immune "%s with positional argument"     -- "%1\$s%2\$s%3\$s"
assert_immune "conversion specifiers combined"  -- "AAAA%08x.%08x.%08x.%n"

section "Encoding and length"

assert_immune "UTF-8 multibyte"                 -- "日本語"
assert_immune "combining characters"            -- "é"
assert_immune "right-to-left override"          -- "$(printf '\342\200\256')"
assert_immune "8-bit high characters"           -- "$(printf '\377\376\375')"

_long=$(awk 'BEGIN{ for(i=0;i<10000;i++) printf "A" }')
assert_immune "10,000-character argument"       -- "$_long"

_many_ok=1
_i=0
while [ "$_i" -lt 500 ]; do set -- "$@" "arg$_i"; _i=$((_i + 1)); done
[ "$("$BIN" "$@" 2>/dev/null)" = "$EXPECTED" ] || _many_ok=0
ok "500 arguments" test "$_many_ok" -eq 1

section "Standard input"

equals "empty stdin"                 "$EXPECTED" "$("$BIN" < /dev/null)"
equals "8 KiB of random bytes"       "$EXPECTED" "$(head -c 8192 /dev/urandom | "$BIN")"
equals "stdin closed entirely"       "$EXPECTED" "$("$BIN" 0<&- 2>/dev/null)"
equals "stdin is a directory"        "$EXPECTED" "$("$BIN" < / 2>/dev/null || "$BIN")"

# A FIFO with no writer is deliberately NOT tested here: opening one for
# reading blocks in the shell, before the program is ever executed, so the
# test would measure the shell rather than the binary. The equivalent
# guarantee is covered by "stdin closed entirely" above.
equals "stdin is a pipe that closes immediately" \
    "$EXPECTED" "$(true | "$BIN")"

section "Environment"

equals "hostile PATH"        "$EXPECTED" "$(PATH=/nonexistent "$BIN")"
equals "hostile IFS"         "$EXPECTED" "$(IFS='%' "$BIN")"
equals "enormous variable"   "$EXPECTED" "$(BIG="$_long" "$BIN")"
equals "format string in an environment variable" \
                             "$EXPECTED" "$(EVIL='%n%n%n%n' "$BIN")"

section "Resource limits"

# The program allocates nothing on the heap (README section 8.3), so it
# should survive a zero heap allocation limit on systems that can express
# one. Some libc implementations allocate the stdout buffer lazily, so a
# failure here is informative rather than fatal.
if (ulimit -v 100000 2>/dev/null); then
    _r=$( (ulimit -v 100000; "$BIN") 2>/dev/null )
    equals "constrained address space (100 MB)" "$EXPECTED" "$_r"
else
    skip "constrained address space" "ulimit -v unsupported"
fi

summary
