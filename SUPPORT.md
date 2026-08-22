# Support

## Before opening an issue

The overwhelming majority of problems with this program are toolchain or
environment faults rather than defects in six lines of source. Check these
first, in order:

1. **[INSTRUCTIONS.md Part 15](INSTRUCTIONS.md#part-15-troubleshooting)** —
   fifteen common failures with their causes, from `stray '\342' in program`
   (typographic quotes from a word processor) to `Hello, World!/n` (a forward
   slash where a backslash belongs).

2. **Confirm your toolchain works at all:**

   ```bash
   printf 'int main(void){return 0;}' > /tmp/t.c && cc -o /tmp/t /tmp/t.c && /tmp/t && echo OK
   ```

   If that does not print `OK`, the problem is your compiler installation and
   [INSTRUCTIONS.md Part 7](INSTRUCTIONS.md#part-7-installing-a-compiler)
   covers every major platform.

3. **[INSTALL.md section 14](INSTALL.md#14-troubleshooting)** — for
   installation rather than build failures.

4. **[UNINSTALL.md section 10](UNINSTALL.md#10-troubleshooting)** — for
   removal problems, most commonly `make uninstall` run with a different
   `PREFIX` than `make install` was.

## Where to ask

| I want to | Go to |
|---|---|
| Report that the program printed the wrong thing | [Bug report issue](../../issues/new?template=bug_report.yml) |
| Report a factual error in the documentation | [Documentation issue](../../issues/new?template=documentation.yml) |
| Propose a change to what the program does | [Feature request](../../issues/new?template=feature_request.yml) — read [README section 3.1](README.md#31-non-features) first |
| Report a security issue | **Not an issue.** See [SECURITY.md](SECURITY.md) |
| Ask how to run this at all | [INSTRUCTIONS.md](INSTRUCTIONS.md), which assumes you own nothing |
| Ask why the source file is 2,718 lines | [README section 1.2](README.md#12-what-the-source-file-contains) |
| Contribute a change | [CONTRIBUTING.md](CONTRIBUTING.md) |

## What to include

A report is actionable when it contains:

```bash
uname -a
cc --version
./hello | od -c      # what was actually emitted, not what it looked like
./hello; echo $?     # the exit status
```

`od -c` is the important one. Trailing whitespace, a missing newline, and
CRLF line endings are all invisible in a screenshot and obvious in a byte
dump.

## Response expectations

This is not commercially supported software. Issues are read; responses are
not guaranteed on any timeline.

Documentation corrections accompanied by a source are the most likely
contribution to receive a prompt response, because they are the most likely
to be right. See [CONTRIBUTING.md](CONTRIBUTING.md).
