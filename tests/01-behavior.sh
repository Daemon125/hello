#!/bin/sh
# Behavioural conformance.
#
# Verifies the program's complete observable contract as specified in
# README section 6: fourteen bytes on stdout, nothing on stderr, exit
# status 0, and total indifference to its environment.
set -u
. "$(dirname "$0")/lib.sh"

section "Output"

equals "stdout is exactly the specified string" \
    "Hello, World!" "$("$BIN")"

equals "output is 14 bytes (13 visible + LF)" \
    "14" "$("$BIN" | wc -c | tr -d ' ')"

equals "output is exactly one line" \
    "1" "$("$BIN" | wc -l | tr -d ' ')"

equals "output terminates with LF, not CRLF" \
    "0a" "$("$BIN" | od -An -tx1 | tr -d ' \n' | sed 's/.*\(..\)$/\1/')"

equals "no carriage returns anywhere in output" \
    "0" "$("$BIN" | tr -dc '\r' | wc -c | tr -d ' ')"

equals "output is pure 7-bit ASCII" \
    "0" "$("$BIN" | LC_ALL=C tr -d '\000-\177' | wc -c | tr -d ' ')"

section "Exit status"

"$BIN" >/dev/null 2>&1
equals "exit status is 0" "0" "$?"

section "Stream discipline"

equals "stderr is empty" \
    "" "$("$BIN" 2>&1 >/dev/null)"

equals "stdin is never read" \
    "unconsumed" "$( { "$BIN" >/dev/null; cat; } <<'STDIN'
unconsumed
STDIN
)"

section "Output destination independence"

equals "identical through a pipe" \
    "Hello, World!" "$("$BIN" | cat)"

_tmp=$(mktemp)
"$BIN" > "$_tmp"
equals "identical when redirected to a file" \
    "Hello, World!" "$(cat "$_tmp")"
rm -f "$_tmp"

equals "identical through two pipes" \
    "Hello, World!" "$("$BIN" | cat | cat)"

equals "survives a truncating consumer" \
    "Hello" "$("$BIN" | cut -c1-5)"

section "Determinism"

equals "two consecutive runs agree" \
    "$("$BIN")" "$("$BIN")"

_hash1=$("$BIN" | cksum)
_i=0
while [ "$_i" -lt 50 ]; do
    if [ "$("$BIN" | cksum)" != "$_hash1" ]; then
        echo "divergence at iteration $_i" >&2
        exit 1
    fi
    _i=$((_i + 1))
done
ok "50 runs produce byte-identical output" true

section "Environment independence"

equals "unaffected by LANG=C" \
    "Hello, World!" "$(LANG=C "$BIN")"

equals "unaffected by LC_ALL=tr_TR.UTF-8" \
    "Hello, World!" "$(LC_ALL=tr_TR.UTF-8 "$BIN" 2>/dev/null)"

equals "unaffected by TERM=dumb" \
    "Hello, World!" "$(TERM=dumb "$BIN")"

equals "unaffected by an empty environment" \
    "Hello, World!" "$(env -i "$BIN" 2>/dev/null || "$BIN")"

summary
