# hello

> A program that prints `Hello, World!` to standard output and exits.

[![CI](https://github.com/OWNER/REPO/actions/workflows/ci.yml/badge.svg)](https://github.com/OWNER/REPO/actions/workflows/ci.yml)
[![CodeQL](https://github.com/OWNER/REPO/actions/workflows/codeql.yml/badge.svg)](https://github.com/OWNER/REPO/actions/workflows/codeql.yml)
[![Nightly](https://github.com/OWNER/REPO/actions/workflows/nightly.yml/badge.svg)](https://github.com/OWNER/REPO/actions/workflows/nightly.yml)

**Status:** Stable. Feature-complete since 1972.
**Language:** C (C99 or later; also builds as C89 with one caveat, see [Building](#5-building))
**Lines of code:** 6
**Lines of documentation:** 2,712 (in-source) + this file + [INSTRUCTIONS.md](INSTRUCTIONS.md)
**Documentation-to-code ratio:** 452:1
**Test coverage:** 100%
**Open issues:** 0
**Dependencies:** 1 (`libc`, which you already have)

---

## Table of Contents

1. [What This Is](#1-what-this-is)
2. [Quick Start](#2-quick-start)
3. [Features](#3-features)
4. [Architecture](#4-architecture)
5. [Building](#5-building)
6. [API Reference](#6-api-reference)
7. [Configuration](#7-configuration)
8. [Performance](#8-performance)
9. [Security](#9-security)
10. [Portability](#10-portability)
11. [Testing](#11-testing)
12. [Known Limitations](#12-known-limitations)
13. [Roadmap](#13-roadmap)
14. [FAQ](#14-faq)
15. [Contributing](#15-contributing)
16. [Changelog](#16-changelog)
17. [Citation](#17-citation)
18. [License](#18-license)
19. [Acknowledgments](#19-acknowledgments)

---

## 1. What This Is

`hello` is a complete, self-contained C program that writes the fourteen bytes
`Hello, World!\n` to file descriptor 1 and returns an exit status of 0.

That is the entire behavior. There are no command-line options, no
configuration files, no network activity, no persistent state, and no plugins.
The program does not read input. It cannot be made to do anything else.

### 1.1 Why it exists

Because the first program anyone writes in a new language is not a test of the
language. It is a test of everything except the language: the editor, the
compiler, the linker, the loader, the shell, the terminal, and the several
dozen other things between a keystroke and a glowing pixel.

A program that computes something can fail in two ways you cannot tell apart —
the toolchain is broken, or your logic is wrong. This program has no logic to
get wrong. If it prints, the apparatus works. If it does not, the apparatus is
where the problem is. That diagnostic property is worth more than any feature
we could add, and every feature we could add would destroy it.

### 1.2 What the source file contains

[`hello.c`](hello.c) is 2,718 lines. Six of them execute. The remaining 2,712
are a three-volume dissertation, in block comments, covering:

- **Volume I** — the history of the English language, from Proto-Indo-European
  through to the etymology of the two words in the string
- **Volume II** — the history of C, from ALGOL 60 through the Unix rewrite of
  1973 to the C23 standard
- **Volume III** — the philosophical implications of the phrase, covering
  phatic communion, speech-act theory, the symbol grounding problem, rites of
  passage, and the meaning of `return 0`

All of it is deleted at translation phase 3 and has no effect on the compiled
output. See §18.1 of the source for the phase list.

### 1.3 Who this is for

- People learning C, who should read §1 and §2 and stop
- People who have just bought a computer and do not yet know what a compiler
  is, who should read [INSTRUCTIONS.md](INSTRUCTIONS.md) instead
- People verifying a new toolchain, for whom this is a smoke test
- People who wanted to know why English spelling is like that

---

### 1.4 Documentation map

| Document | Read it when |
|---|---|
| **README.md** | You want the technical reference. You are here. |
| [INSTRUCTIONS.md](INSTRUCTIONS.md) | You have never compiled anything. Begins by assuming you do not own a computer. |
| [INSTALL.md](INSTALL.md) | You want to install it system-wide, package it, or verify a release artifact. |
| [UNINSTALL.md](UNINSTALL.md) | You want it gone. Complete rather than approximate; see its section 1. |
| [CONTRIBUTING.md](CONTRIBUTING.md) | You want to change something. |
| [SUPPORT.md](SUPPORT.md) | Something is wrong and you want to know where to ask. |
| [SECURITY.md](SECURITY.md) | You found a vulnerability, or want the threat model. |
| [CHANGELOG.md](CHANGELOG.md) | You want the version history, back to 1972. |
| [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) | You want the conduct rule. It is one sentence, plus what happens if you ignore it. |
| [`hello.c`](hello.c) | You want the reasoning behind every decision above. 2,712 lines. |
| `man ./hello.1` | You want the manual page. |

---

## 2. Quick Start

```bash
cc -o hello hello.c && ./hello
```

Expected output:

```
Hello, World!
```

Expected exit status: `0`.

If that worked, you are done and may close this file. If it did not, see
[INSTRUCTIONS.md](INSTRUCTIONS.md), which assumes nothing, including that you
own a computer.

To install it rather than run it in place, see [INSTALL.md](INSTALL.md):

```bash
make && sudo make install
```

To remove it, see [UNINSTALL.md](UNINSTALL.md). Both are complete: installation
places five files and creates no configuration, state, or cache anywhere.

---

## 3. Features

| Feature | Status |
|---|---|
| Prints `Hello, World!` | Supported |
| Exits cleanly | Supported |
| Returns a meaningful exit status | Supported |
| Flushes output before exiting | Supported |
| Works when stdout is redirected | Supported |
| Works when stdout is a pipe | Supported |
| Works when stdout is closed | Supported (silently; see §12.3) |
| Thread-safe | Yes, vacuously |
| Reentrant | Yes, vacuously |
| Async-signal-safe | No (`printf` is not; see §9.4) |
| Localized | No (see §12.1) |
| Configurable | No (see §7) |

### 3.1 Non-features

The following have been considered and deliberately rejected. Requests to add
them will be closed.

| Not a feature | Rationale |
|---|---|
| A `--name` flag to greet someone specific | Destroys the diagnostic property in §1.1 |
| Reading the greeting from a config file | Adds a failure mode with no benefit |
| Colored output | Requires terminal detection; see §7.2 |
| A `--version` flag | The program has no version. It has an epoch. |
| Internationalization | See §12.1 |
| A plugin architecture | No. |
| Logging | The program's entire output *is* the log |
| A web interface | No. |
| Telemetry | Absolutely not. |

---

## 4. Architecture

The program is a single translation unit with no internal structure. What
follows is the architecture of everything *underneath* it, which is where all
of the actual complexity lives.

```
   hello.c  (2,718 lines; 6 significant)
      |
      | phase 1-4: preprocessing
      |            comments -> single space  (2,712 lines discarded here)
      |            #include <stdio.h> -> ~1,500 lines inserted
      v
   translation unit  (~1,500 lines)
      |
      | phase 7: compile
      v
   hello.o   (object code + 15 bytes of .rodata)
      |
      | phase 8: link
      | + crt0 (startup)  + libc (printf, exit)
      v
   hello     (~33 KB executable)
      |
      | execve(2)
      v
   [ loader ] -> [ crt0 ] -> main() -> printf()
                                          |
                                          | copy into stdout's buffer
                                          v
                                     [ line buffer ]
                                          |
                                          | '\n' triggers flush
                                          v
                                       write(2)
                                          |
                                          | trap -> ring 0
                                          v
                                   [ kernel: vfs ]
                                          |
                                          v
                                   [ tty driver ]
                                          |
                                          v
                              [ pty -> shell -> emulator ]
                                          |
                                          v
                          [ font rasterizer -> compositor ]
                                          |
                                          v
                              [ GPU -> display -> panel ]
                                          |
                                          v
                                       photons
                                          |
                                          v
                                    [ retina -> V1 ]
                                          |
                                          v
                              [ language cortex: English ]
                                          |
                                          v
                                    "I have been greeted"
```

Every stage must work. Any one failing produces nothing. This is the entire
value proposition of the program: it is the smallest question you can ask that
still requires the whole stack to answer.

### 4.1 Data flow

There is one datum. It is fifteen bytes (fourteen printable plus a NUL
terminator) and it lives in `.rodata`. It is never modified, never copied more
than once, and never freed, because it was never allocated.

### 4.2 Repository layout

```
.
├── hello.c                     the program, and 2,712 lines of commentary
├── hello.1                     manual page; `man ./hello.1`
├── Makefile                    build, verify, install; see section 5.7
├── README.md                   this file
├── INSTRUCTIONS.md             how to run it, starting from owning nothing
├── INSTALL.md                  installation, packaging, verification
├── UNINSTALL.md                complete removal
├── CONTRIBUTING.md             how to contribute
├── CHANGELOG.md                version history, back to 1972
├── SECURITY.md                 threat model and reporting
├── SUPPORT.md                  where to ask what
├── CODE_OF_CONDUCT.md          be civil; assume competence
├── LICENSE                     public domain (Unlicense)
├── CITATION.cff                citation metadata
├── .editorconfig               editor settings, enforced by `make lint`
├── .gitignore                  build-product exclusions; see section 11.9
├── tests/
│   ├── lib.sh                  assertion helpers (POSIX sh)
│   ├── run.sh                  suite runner
│   ├── links.py                link and cross-reference checker
│   ├── 01-behavior.sh          the observable contract
│   ├── 02-input-immunity.sh    evidence for the zero-attack-surface claim
│   ├── 03-standards.sh         C89 through C23, plus C++
│   ├── 04-binary.sh            sections, linkage, reproducibility
│   ├── 05-docs.sh              the documentation's own claims
│   ├── 06-repository.sh        .gitignore coverage and tracked-file state
│   └── 07-project-docs.sh      community standards; install round-trip
└── .github/
    ├── CODEOWNERS              review routing
    ├── dependabot.yml          the pipeline's own dependencies
    ├── PULL_REQUEST_TEMPLATE.md
    ├── ISSUE_TEMPLATE/         bug, documentation, and feature forms
    └── workflows/
        ├── ci.yml              the pipeline; see section 11.7
        ├── codeql.yml          security scanning
        └── nightly.yml         unchanged source against moving toolchains
```

### 4.3 Control flow

```
crt0 -> main -> printf -> vfprintf -> memcpy -> write -> return -> exit
```

No branches. No loops in the program itself (`printf` and `memcpy` have
their own). Cyclomatic complexity: 1.

---

## 5. Building

### 5.1 The one-liner

```bash
cc -o hello hello.c
```

### 5.2 Recommended, with warnings enabled

```bash
cc -Wall -Wextra -pedantic -std=c99 -O2 -o hello hello.c
```

This is the invocation the project is verified against. It produces no
diagnostics.

### 5.3 The full matrix

| Compiler | Invocation | Result |
|---|---|---|
| GCC | `gcc -Wall -Wextra -pedantic -o hello hello.c` | Clean |
| Clang | `clang -Wall -Wextra -pedantic -o hello hello.c` | Clean |
| MSVC | `cl hello.c` | Clean |
| TCC | `tcc -o hello hello.c` | Clean, and instant |
| ICC | `icc -o hello hello.c` | Clean |
| `cc` | `cc -o hello hello.c` | Clean |

### 5.4 Standards conformance

| Standard | Builds | Notes |
|---|---|---|
| C89/C90 | Yes | `-std=c89 -pedantic` is clean |
| C99 | Yes | Reference configuration |
| C11 | Yes | |
| C17 | Yes | |
| C23 | Yes | |
| K&R C (1978) | No | `int main(void)` is fine, but see §5.5 |
| C++98 through C++23 | Yes | Compiles as valid C++ unmodified |

### 5.5 A note on the 1978 version

The original from the first page of K&R:

```c
main()
{
    printf("hello, world\n");
}
```

This does not compile cleanly under any modern standard. It omits the
`#include`, which makes the call to a variadic function without a visible
prototype *undefined behavior* under C89 and later; it relies on implicit
`int`, removed in C99; and its K&R-style declaration was removed from the
language entirely in C23. The canonical first program of the discipline is no
longer valid in the language it introduced.

### 5.6 Optimization

`-O2` and `-O3` produce identical output to `-O0` for this program, because
there is nothing to optimize. `-Os` is marginally smaller. Link-time
optimization has no effect. Profile-guided optimization has no effect, though
generating the profile is a valid way to spend an afternoon.

### 5.7 The Makefile

The program needs no build system; `cc -o hello hello.c` is sufficient and is
what INSTRUCTIONS.md tells a first-time reader to type. The Makefile exists for
the verification around it, so that the same commands run locally and in CI and
the two cannot drift apart.

| Target | Effect |
|---|---|
| `make` | Build with `-Wall -Wextra -pedantic -Werror` |
| `make test` | Build and run all five suites |
| `make lint` | Whitespace, encoding, terminator, and shell-syntax checks |
| `make analyze` | cppcheck, clang-tidy, and `gcc -fanalyzer` |
| `make sanitize` | Build and run under ASan and UBSan |
| `make valgrind` | Run under valgrind, if installed |
| `make matrix` | Build under every standard and optimization level |
| `make stats` | Print the repository's quantitative figures |
| `make bench` | Time the program against the figures in section 8.1 |
| `make dist` | Produce a source tarball |
| `make clean` | Remove build products |

### 5.8 Static linking

```bash
cc -static -o hello hello.c
```

Produces a binary in the vicinity of 800 KB, of which approximately 0.002% is
this program. The rest is `libc`, which is included in its entirety because
the linker cannot easily prove which parts of `printf`'s machinery you will not
reach.

---

## 6. API Reference

### 6.1 `main`

```c
int main(void);
```

The program's sole function and entry point.

**Parameters:** None. The `(void)` is significant: an empty parameter list in C
means *unspecified*, not *none*, and would permit callers to pass arguments
that would not be checked. This program is called by `crt0` with `argc` and
`argv`, which it ignores, which is legal.

**Returns:** `0`, always. See §6.2.

**Thread safety:** `main` is called once, on the initial thread. It is not
designed to be called again, though nothing prevents you from doing so, and if
you do it will print twice.

**Errors:** `main` does not check the return value of `printf`, which is a
deliberate simplification and technically a defect. See §12.2.

### 6.2 Exit status

| Value | Meaning | Emitted when |
|---|---|---|
| `0` | Success | Always |

The exit status space is 8 bits wide, giving 256 possible values. This program
uses one of them. The other 255 are reserved for a version of the program that
can fail, which does not exist.

Note that `0` does not mean *the greeting was received*, or *the greeting was
good*. It means *nothing went wrong*. The system is not equipped to ask for
more than that, and this is discussed at length in §25.3 of the source.

### 6.3 Standard streams

| Stream | Used | Notes |
|---|---|---|
| `stdin` (fd 0) | No | Never read. The program cannot be interacted with. |
| `stdout` (fd 1) | Yes | The entire interface |
| `stderr` (fd 2) | No | Nothing to report |

### 6.4 Signals

The program installs no signal handlers and inherits the default disposition
for everything. Its execution window is short enough (see §8) that delivering a
signal to it deliberately requires either a debugger or unusual luck.

---

## 7. Configuration

The program has no configuration. There is no config file, no environment
variable it reads, and no command-line option it accepts. Arguments passed to
it are ignored:

```bash
./hello --help          # prints Hello, World!
./hello --version       # prints Hello, World!
./hello --format=json   # prints Hello, World!
./hello < /dev/urandom  # prints Hello, World!
```

This is intentional. See §3.1.

### 7.1 Things that nevertheless affect behavior

Despite the above, the following genuinely change what happens, none of them
through anything the program does:

| Variable | Effect |
|---|---|
| Redirection of stdout | Changes buffering from line-buffered to fully buffered (see §8.4) |
| `TERM` | Not read by the program, but determines how the *terminal* renders the bytes |
| `LANG` / `LC_ALL` | Not read by the program. Affects nothing, because the string is pure ASCII. |
| `LD_PRELOAD` | Can replace `printf` entirely, at which point all bets are off |
| `LD_LIBRARY_PATH` | Determines *which* `libc` supplies `printf` |

### 7.2 On colored output

Repeatedly requested; permanently rejected. Emitting ANSI escape sequences
requires detecting whether stdout is a terminal, which requires `isatty`, which
adds a branch, a header, and a failure mode — and produces garbage in the case
where the detection is wrong. The cost is real and the benefit is decorative.

---

## 8. Performance

### 8.1 Benchmarks

Measured on a modern laptop, output to `/dev/null`, best of 1000 runs:

| Phase | Time |
|---|---|
| `execve` and loader | ~400 µs |
| Dynamic linking | ~300 µs |
| `crt0` and stream init | ~50 µs |
| **`main` body** | **~2 µs** |
| `write(2)` syscall | ~1.5 µs |
| Exit and teardown | ~30 µs |
| **Total wall clock** | **~800 µs** |

The program itself accounts for roughly 0.25% of its own runtime. The other
99.75% is the operating system starting and stopping it. Optimizing the program
is therefore not merely unnecessary but arithmetically pointless; a 100%
speedup of `main` would improve total runtime by two microseconds.

Statically linked, total wall clock drops to roughly 400 µs, entirely by
eliminating the dynamic linker.

### 8.2 Complexity

| Metric | Value |
|---|---|
| Time complexity | O(1) |
| Space complexity | O(1) |
| Cyclomatic complexity | 1 |
| Halstead difficulty | Negligible |
| Maximum call depth | 5 |

### 8.3 Memory footprint

| Segment | Size |
|---|---|
| `.text` (this program's own code) | ~30 bytes |
| `.rodata` (the string) | 15 bytes |
| `.data` | 0 |
| `.bss` | 0 |
| Heap allocated by this program | 0 bytes |
| Heap allocated by `libc` on its behalf | ~4 KB (the stdout buffer) |
| Resident set size at peak | ~1.5 MB |

Note the ratio in the last two rows. The program allocates nothing; the runtime
allocates four kilobytes on its behalf to hold fourteen bytes; and the process
occupies a megabyte and a half of RSS, essentially all of it mapped `libc`.

### 8.4 Buffering

`stdout` is line-buffered when it is a terminal and fully buffered (typically
4 KB or 8 KB) otherwise. The trailing `\n` triggers the flush in the terminal
case, which is why the output appears immediately rather than at exit.

This is the only thing in the program that is load-bearing for a reason a
beginner would not guess, and it is why the newline is not decorative. In a
long-running program that crashes, output sitting in a full buffer is lost, and
the last line printed is not the last line executed. Every programmer learns
this eventually, usually the hard way.

### 8.5 Scaling

The program does not scale, in the sense that running it twice prints twice.
There is no batching, no connection pooling, and no amortization available.
Horizontal scaling works perfectly: N machines print N greetings with no
coordination, no shared state, and no consistency requirements. This is,
technically, an embarrassingly parallel workload.

---

## 9. Security

This section is longer than the program deserves, because most of it is
genuinely useful and applies to code that is not this program.

### 9.1 Threat model

| Asset | Threat | Assessment |
|---|---|---|
| The string | Disclosure | It is a greeting. It is in the README. |
| The exit status | Tampering | Requires code execution, at which point the attacker has better options |
| Availability | Denial of service | Can be achieved by not running the program |
| Integrity of output | Injection | Not possible; there is no input to inject into |

**Attack surface:** zero. The program reads no input from any source: no
`stdin`, no arguments, no environment variables, no files, no network, no IPC.
An attacker with no code execution has nothing to send it.

This is not a boast. It is the direct consequence of §7, and it is the reason
the program is a useful baseline: any vulnerability found while running it is a
vulnerability in the toolchain, the loader, or `libc`, not in the program.

### 9.2 The format string vulnerability this program does not have

The single most important security property of the source is this line:

```c
printf("Hello, World!\n");
```

and specifically the fact that the format string is a **literal**. Compare:

```c
printf(user_input);              /* CATASTROPHIC */
printf("%s", user_input);        /* correct */
```

If the format string comes from an attacker, then every conversion specifier
in it is executed. `%x` leaks stack contents. `%s` dereferences whatever is in
the argument position and prints memory until it hits a zero byte. And `%n`
*writes* the number of characters printed so far to a pointer taken from the
argument list, which converts a printing function into an arbitrary memory
write and, from there, into arbitrary code execution.

This is CWE-134. It was the basis of a large family of remote exploits from the
late 1990s onward, and it is still found in new code every year.

Modern compilers help: GCC and Clang both accept `-Wformat-security`, and
`-Wformat-nonliteral` will flag any non-constant format string. Both are worth
enabling in real projects. Neither fires on this program, because there is
nothing here to fire on.

### 9.3 The NUL terminator

The string in `.rodata` is fifteen bytes: fourteen visible plus a terminating
zero. That single byte is the whole of C's string representation and the source
of an enormous share of the memory-safety defects of the last four decades.

BCPL and B stored an explicit length. Ritchie chose a sentinel instead, because
it cost one byte rather than one word — a decision that was straightforwardly
correct on a machine with 24 KB of core, and which has cost the industry an
amount of money that is difficult to estimate but is not small. A string that
loses its terminator does not end; it continues into whatever is adjacent.

This program cannot suffer from that. Its string is a compile-time constant in
read-only memory and is never copied, concatenated, or modified.

### 9.4 Async-signal-safety

`printf` is **not** async-signal-safe. It takes a lock on the stream and
manipulates a buffer, and calling it from a signal handler while it is already
executing on the main thread can deadlock or corrupt the buffer.

This program never calls it from a handler, because it installs no handlers.
But the general rule matters: inside a signal handler, `write(2)` is safe and
`printf(3)` is not. This is the most commonly violated rule in beginner
systems code, and it is violated precisely because `printf` is the first
function anyone learns.

### 9.5 Supply chain

The program has one dependency, `libc`, which is supplied by the operating
system and which you are already trusting with everything else on the machine.
There is no package manager, no lockfile, no transitive dependency tree, and
nothing to audit.

The compiler is a different matter. Ken Thompson's 1984 Turing Award lecture,
*Reflections on Trusting Trust*, describes a compiler modified to insert a
backdoor into a specific program, and to insert the backdoor-inserting code
into any compiler it compiles — so that the malicious source can be removed
entirely while the behavior persists indefinitely through generations of
self-hosted compilers. The example program Thompson used in the lecture was
the Unix `login` command. The relevant point for this README is that no amount
of reading `hello.c` can tell you what the compiled binary does, and this is
not a hypothetical.

### 9.6 Reporting security issues

The full policy, threat model, and supported-version table are in
[SECURITY.md](SECURITY.md). Report privately via GitHub's
**Security → Report a vulnerability** control rather than a public issue.

If you find a security vulnerability in a six-line program that reads no
input, please open an issue. It will be the most interesting thing anyone
reads that week.

Note that such a finding would almost certainly be a defect in the toolchain
or in `libc` rather than in this repository, and should be reported upstream
as well.

---

## 10. Portability

### 10.1 Verified platforms

| Platform | Status |
|---|---|
| Linux (glibc) | Verified |
| Linux (musl) | Verified |
| macOS | Verified |
| FreeBSD / OpenBSD / NetBSD | Expected clean |
| Windows (MSVC) | Expected clean |
| Windows (MinGW / Cygwin / WSL) | Expected clean |
| Solaris / illumos | Expected clean |
| AIX / HP-UX | Expected clean |
| Any hosted C implementation | Guaranteed by the standard |

### 10.2 Freestanding implementations

The program requires a **hosted** implementation, because it requires `stdio.h`
and a `main` that is called by a runtime. On a freestanding implementation —
an embedded target with no operating system — none of that exists, and the
program will not build.

The equivalent on such a target is to write bytes directly to a UART register,
which is arguably closer to the spirit of the thing, since it removes every
layer between the program and the wire.

### 10.3 Assumptions

The program assumes:

- A hosted implementation with a conforming `stdio`
- That file descriptor 1 exists and is writable (it degrades silently if not)
- An execution character set in which the literal's characters are
  representable — true for ASCII, UTF-8, and every ISO-8859 variant

The program does **not** assume:

- Any particular integer width, endianness, or pointer size
- A specific operating system
- A terminal
- That anyone is watching

### 10.4 EBCDIC

On an EBCDIC system the source characters map to entirely different byte
values, and the program still works, because the compiler translates the
literal into the execution character set. `H` is `0x48` in ASCII and `0xC8` in
EBCDIC, and neither the source nor the programmer needs to know which.

This is a genuine and under-appreciated piece of C's design, and it is why the
standard talks about *character sets* rather than about numbers.

---

## 11. Testing

### 11.1 The test

```bash
test "$(./hello)" = "Hello, World!" && echo PASS || echo FAIL
```

### 11.2 The full suite

```bash
#!/bin/sh
# Complete test suite. Exit 0 on success.

# 1. Output is exactly correct
[ "$(./hello)" = "Hello, World!" ] || { echo "FAIL: output"; exit 1; }

# 2. Exit status is 0
./hello > /dev/null; [ $? -eq 0 ] || { echo "FAIL: status"; exit 1; }

# 3. Nothing is written to stderr
[ -z "$(./hello 2>&1 > /dev/null)" ] || { echo "FAIL: stderr"; exit 1; }

# 4. Output is exactly 14 bytes
[ "$(./hello | wc -c)" -eq 14 ] || { echo "FAIL: length"; exit 1; }

# 5. Behavior is identical when stdout is a pipe
[ "$(./hello | cat)" = "Hello, World!" ] || { echo "FAIL: pipe"; exit 1; }

# 6. Arguments are ignored
[ "$(./hello --nonsense)" = "Hello, World!" ] || { echo "FAIL: argv"; exit 1; }

# 7. Idempotent across runs
[ "$(./hello)" = "$(./hello)" ] || { echo "FAIL: determinism"; exit 1; }

echo "PASS (7/7)"
```

### 11.3 Coverage

100% line coverage, 100% branch coverage, 100% path coverage. There is one
path. It is covered.

This is worth noting as the only program for which those three numbers are
simultaneously meaningful, achievable, and completely uninformative.

### 11.4 Fuzzing

Not applicable. Fuzzing requires an input to mutate.

### 11.5 Property-based testing

The program satisfies exactly one property:

```
for all invocations i: output(i) == "Hello, World!\n"
```

This has been verified across a large number of invocations and no counter-
example has been found.

### 11.6 Benchmarking regressions

There is no CI budget for performance regressions because §8.1 establishes that
99.75% of runtime is outside the program's control. A regression would indicate
a change in the operating system, not in this repository.

---

### 11.7 Continuous integration

Every push and pull request runs the pipeline in
[`.github/workflows/ci.yml`](.github/workflows/ci.yml). It expands to
roughly 100 jobs.

| Job | What it establishes |
|---|---|
| `lint` | No trailing whitespace, no non-ASCII bytes in the source, balanced comment delimiters, every shell script parses, every file ends with a newline, no compiled binary is tracked, and a full build leaves the working tree clean |
| `build` | 72 combinations: 4 runner images × 2 compilers × 4 standards × 3 optimization levels, each with `-Werror` and each asserting zero diagnostics, correct output, exit status 0, and a 14-byte payload |
| `windows` | MSVC, clang-cl, and MinGW, with CRLF stripped before comparison |
| `suites` | All five test suites on Linux and macOS, under both GCC and Clang |
| `sanitizers` | ASan, UBSan, MSan, TSan, LSan, and ASan+UBSan combined |
| `analysis` | `gcc -fanalyzer`, cppcheck, clang-tidy, scan-build, and a dedicated format-string audit |
| `cross` | aarch64, armhf, riscv64, ppc64le, and s390x, each cross-compiled and executed under QEMU |
| `historical` | tcc, strict C89 with `-pedantic-errors`, and four C++ standards |
| `binary` | Section placement, linkage count, and reproducible-build verification |
| `docs` | Section 11.8, plus the community-standards checklist and an install/uninstall round-trip |
| `benchmark` | Advisory only; see section 11.6 |
| `ci` | A gate requiring every job above to have succeeded |

The `cross` matrix includes s390x specifically because it is big-endian. The
program serializes no multi-byte integers and should be entirely indifferent
to byte order; that job is what makes this a tested claim rather than an
assumed one.

### 11.8 The documentation is tested

Documentation that states figures goes stale silently. Every quantitative
claim in this README and in INSTRUCTIONS.md is therefore an assertion, checked
on every commit by [`tests/05-docs.sh`](tests/05-docs.sh), which computes the
repository's real figures and fails the build when the prose disagrees.

It verifies:

- The stated line counts, significant-line count, and documentation-to-code
  ratio, against `hello.c` as it actually is
- That the program's documented output matches its actual output, byte for byte
- That the invocation in section 5.2 compiles and emits no diagnostics, since
  that is claimed here without qualification
- That the test suite printed in section 11.2 passes when extracted from this
  file and executed
- That every internal link resolves to a real heading, every file link to a
  real file, and every reference to a numbered section of `hello.c` to a
  section that exists
- That every numbered section across the four numbered documents is unique
  and that none are skipped — 204 of them, checked by
  [`tests/sections.py`](tests/sections.py). A missing number breaks every
  reference to it and nothing else, so nothing else would catch it.
- That `make help` prints only the Makefile's comment header, and that the
  set of targets it documents is exactly the set the Makefile declares

If a figure in this README is wrong, CI is red. The correct response is to
change the prose, not the test.

### 11.9 Build products are excluded, and that is tested

[`.gitignore`](.gitignore) excludes every artifact the Makefile and the
pipeline are capable of producing — 25 patterns, from `hello` through the five
cross-compiled binaries to the reproducible-build checksums — plus toolchain
output, debugger bundles, and the droppings of the four editors
INSTRUCTIONS.md Part 6 recommends.

Its patterns are anchored with a leading slash rather than left bare. The
compiled binary is named `hello`, and an unanchored `hello` would also exclude
any directory of that name at any depth, silently, along with its contents.

Coverage is not assumed. [`tests/06-repository.sh`](tests/06-repository.sh)
checks the patterns against a scratch repository containing only this
project's `.gitignore`, so the file is tested rather than the state of
whatever tree it runs in. It then performs a real build and asserts that every
artifact that appeared is excluded — which is what would catch a new output
added to a build rule without a corresponding entry. Inside CI, where a real
checkout exists, it additionally asserts that no compiled binary is tracked
and that every test script is recorded with mode 100755, since a suite
committed as 100644 fails with "permission denied" for a reason invisible in a
diff.

`.gitignore` section 5 sets out why a binary must not be committed, and
section 7 covers what to do when one already has been. The short version of
the latter is that adding a pattern does not untrack anything: `.gitignore`
governs untracked files only.

### 11.10 What the pipeline is actually for

The program cannot regress. It is six lines, it has no branches, and its
behavior is fully specified by fourteen bytes.

Everything underneath it can and does regress. Compilers add diagnostics,
standard libraries change buffering, linkers change defaults, runner images
replace their toolchains, and new standards deprecate constructs that were
correct for thirty years — section 5.5 records a case where exactly that
happened to this program's own canonical form.

The pipeline exists to detect the day one of those changes reaches these six
lines, which is why the [`nightly`](.github/workflows/nightly.yml) workflow
rebuilds unchanged source against pre-release toolchains on a schedule. The
source is the control; the toolchain is the variable.

---

## 12. Known Limitations

### 12.1 The greeting is not localized

The program greets in English regardless of the user's locale. This is a real
limitation and it is not going to be fixed, for two reasons.

The practical one: localization requires `gettext` or equivalent, a message
catalog, a build step, an installation path, and a runtime dependency — which
is several orders of magnitude more machinery than the program itself, all of
it capable of failing, in a program whose only purpose is to fail in as few
ways as possible.

The honest one: the program is in English for the same reason the rest of
computing is, which is a chain of mid-century historical accidents with no
linguistic content, discussed in §7.5 of the source. Localizing the greeting
would obscure that rather than address it.

### 12.2 The return value of `printf` is not checked

`printf` returns the number of characters written, or a negative value on
error. This program discards it. If the write fails — the disk is full, the
pipe is closed, the terminal has gone away — the program will not notice and
will still exit `0`, reporting success for something that did not happen.

This is a genuine defect. It is present in essentially every published version
of this program including K&R's. Fixing it would require:

```c
if (printf("Hello, World!\n") < 0)
    return 1;
```

which doubles the program's cyclomatic complexity and introduces a code path
that is nearly impossible to test. The tradeoff has been made deliberately and
in favor of the simpler version, and it is documented here rather than hidden.

### 12.3 Silent failure when stdout is closed

```bash
./hello >&-
```

The write fails, and per §12.2 the failure is not detected, and the program
exits `0` having printed nothing. This is the specific case in which the exit
status lies.

### 12.4 The exclamation point is not canonical

The original is `hello, world` — lowercase, no exclamation point. This
repository uses the redacted popular form, which is what people expect. The
discrepancy is documented in §8.4 of the source rather than silently
corrected.

### 12.5 The documentation is 452 times the size of the program

Working as intended.

---

## 13. Roadmap

| Version | Scope | Status |
|---|---|---|
| 1.0.0 | Print `Hello, World!` | Shipped, 1972 |
| 1.0.1 | Add `#include <stdio.h>` | Shipped, 1989 |
| 1.0.2 | Add explicit `int` and `return` | Shipped, 1999 |
| 1.1.0 | Documentation | Shipped, this repository |
| 2.0.0 | *(none planned)* | — |

There is no 2.0. The program is complete. A program that is finished is not a
dead project; it is a rare and desirable state, and the industry's inability to
recognize it is a cultural problem rather than a technical one.

Proposals for `Goodbye, World` as a separate binary have been declined on the
grounds that the program already implements it, in §25 of the source, by
exiting.

---

## 14. FAQ

**Q: Why is the documentation so much larger than the program?**
A: Because the program is finished and the context is not. A program this
small can be fully specified in an afternoon; the six thousand years of
linguistic history and fifty years of systems history that produced it
cannot. The ratio reflects where the remaining complexity actually lives.

**Q: Do I need to read `hello.c` to use this?**
A: No. You need to read six lines of it, and they are at the bottom.

**Q: Is the history in the source comments accurate?**
A: Yes, with two flagged exceptions. The hatching-chick origin of the phrase is
Kernighan's own recollection, and he has said he cannot locate the cartoon, so
it is a memory rather than a citation. The creolization and Celtic-substrate
claims about Middle English are marked as contested where they appear, because
they are.

**Q: Why `int main(void)` and not `void main()`?**
A: Because `void main()` is not valid C. The standard specifies `int main(void)`
or `int main(int, char **)` for hosted implementations. Compilers that accept
`void main()` are doing you no favors.

**Q: Why is `return 0;` there if C99 makes it optional?**
A: Because relying on an implicit return from `main` requires the reader to
know a rule that most readers do not know, and the cost of writing it out is
one line.

**Q: Can I use this in production?**
A: Yes. It is the most thoroughly tested program in this repository.

**Q: Is it Y2K compliant? Is it 2038 compliant?**
A: The program does not know what time it is and never will.

**Q: Does it work offline?**
A: Yes.

**Q: Is there a Docker image?**
A: The Docker image would be four orders of magnitude larger than the program.
Use the compiler.

---

## 15. Contributing

The full guide is [CONTRIBUTING.md](CONTRIBUTING.md), which covers development
setup, style, commit conventions, and the rule that catches most contributors
(section 11.8: the documentation is tested). [SUPPORT.md](SUPPORT.md) covers
where to file what. The summary follows.

### 15.1 What will be accepted

- Corrections to factual errors in the documentation, with a source
- Portability fixes for platforms in §10.1 marked *expected*
- Typos

### 15.2 What will not be accepted

- Features (see §3.1)
- Reformatting the source comments
- Removing the source comments
- Additions to the source commentary. Volumes I through III are considered
  complete; corrections are welcome, expansions are not.

### 15.3 Pipeline

Every pull request runs the full pipeline described in section 11.7. Before
opening one:

```bash
make lint && make test && make matrix
```

If `tests/05-docs.sh` fails because you changed the size of `hello.c`, update
the figures in the prose. The test computes them; it does not accept them.

### 15.4 Style

Match the surrounding code. This is unusually easy here.

### 15.5 Code of Conduct

The [Code of Conduct](CODE_OF_CONDUCT.md) is one rule — be civil, assume
competence, criticise the work and not the person — plus one project-specific
clause: this repository's documentation is aimed partly at people writing their
first program, so condescension toward beginners is out of place here in a way
it might not be elsewhere.

Otherwise: be as courteous to other contributors as the program is to the world. Note that
the program greets unconditionally, expects nothing in return, and cannot be
disappointed, which is a high bar.

---

## 16. Changelog

The complete history, in [Keep a Changelog](https://keepachangelog.com/) format
and running back to 1972, is in [CHANGELOG.md](CHANGELOG.md). Recent entries
are summarised here.

### [1.2.0] — 2026-08-22
- Added continuous integration (`.github/workflows/ci.yml`), expanding to
  roughly 100 jobs across 3 operating systems and 5 architectures
- Added CodeQL scanning and a nightly workflow against pre-release toolchains
- Added seven test suites (`tests/`) totalling more than 248 assertions
- Added `tests/05-docs.sh`, which verifies this file's own quantitative
  claims against the repository and fails the build when they disagree
- Added a `Makefile` for local verification
- Added `INSTALL.md`, `UNINSTALL.md`, `CONTRIBUTING.md`, `SECURITY.md`,
  `SUPPORT.md`, `CODE_OF_CONDUCT.md`, `CHANGELOG.md`, `LICENSE`,
  `CITATION.cff`, `.editorconfig`, `.github/CODEOWNERS`, and a `hello.1`
  manual page
- Added `install`, `uninstall`, and `installcheck` targets following the GNU
  conventions for `PREFIX` and `DESTDIR`
- Added `.gitignore`, covering all build artifacts in 25 patterns, verified
  by `tests/06-repository.sh` against a real build rather than assumed
- Corrected the stated line counts and documentation-to-code ratio, which the
  new documentation suite immediately found to be wrong
- No functional change

### [1.1.0] — 2026-08-22
- Added three-volume dissertation to source comments (2,712 lines)
- Added this README
- Added [INSTRUCTIONS.md](INSTRUCTIONS.md)
- No functional change

### [1.0.2] — 1999
- Added explicit `int` return type to `main` (C99 removed implicit `int`)
- Added explicit `return 0;`

### [1.0.1] — 1989
- Added `#include <stdio.h>` (C89 requires a visible prototype for variadic
  functions; its absence was undefined behavior)

### [1.0.0] — 1972
- Initial release
- Prints `hello, world`

---

## 17. Citation

If this repository has contributed to your work, which would be surprising:

```bibtex
@misc{hello2026,
  title        = {Hello, World: An Inquiry into the Descent of a Sentence,
                  the Machine That Utters It, and the Question of Whether
                  Anything Is Meant By It},
  year         = {2026},
  note         = {Three volumes, in C block comments. 2,712 lines of
                  documentation supporting 6 lines of executable code.},
  howpublished = {\texttt{hello.c}}
}
```

For the phrase itself, cite the original:

```bibtex
@techreport{kernighan1972b,
  author      = {Kernighan, Brian W.},
  title       = {A Tutorial Introduction to the Language B},
  institution = {Bell Laboratories},
  year        = {1972}
}

@book{kr1978,
  author    = {Kernighan, Brian W. and Ritchie, Dennis M.},
  title     = {The C Programming Language},
  publisher = {Prentice-Hall},
  year      = {1978}
}
```

---

## 18. License

[Unlicense](LICENSE). Public domain, to the extent that a greeting can be
owned. The phrase has been
in continuous common use since 1972 and any claim over it would be both
unenforceable and rude.

---

## 19. Acknowledgments

**Brian Kernighan**, who wrote the sentence in a Bell Labs memorandum in 1972
and has spent five decades being asked where it came from.

**Dennis Ritchie** (1941–2011), who built the language, co-built the operating
system, and whose death was almost entirely crowded out of the news cycle by
another that week — mourned, as it happened, on devices running his software.

**Ken Thompson**, who wrote an operating system in three weeks and then warned
everyone not to trust the compiler.

**The anonymous scribes of Anglo-Saxon England**, who wrote down a compound
meaning *the age of man* and had no way of knowing where it would end up.

**Thomas Edison**, without whom this program would begin with the word *ahoy*.

---

**See also:** [INSTRUCTIONS.md](INSTRUCTIONS.md) — a complete guide to running
this program, beginning with the purchase of a computer ·
[INSTALL.md](INSTALL.md) · [UNINSTALL.md](UNINSTALL.md) ·
[CONTRIBUTING.md](CONTRIBUTING.md) · [CHANGELOG.md](CHANGELOG.md)
