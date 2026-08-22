# Security Policy

## Supported Versions

| Version | Supported |
|---|---|
| 1.2.x | Yes |
| 1.1.x | Yes |
| 1.0.x | Yes |

All released versions are supported. The program has not changed
functionally since 1972 and there is no version in which a defect could have
been introduced and later fixed.

## Reporting a Vulnerability

Report privately via GitHub's **Security → Report a vulnerability** control,
which opens a private advisory visible only to maintainers. Do not open a
public issue for a suspected vulnerability.

Expect an acknowledgement within 72 hours.

A vulnerability in this program would be genuinely surprising and genuinely
interesting, and will be treated as such rather than dismissed.

## Threat Model

The program reads **no input from any source**: no `stdin`, no command-line
arguments, no environment variables, no files, no network, no IPC. An attacker
without code execution has nothing to send it.

This is not a claim derived from reading six lines. It is tested:
[`tests/02-input-immunity.sh`](tests/02-input-immunity.sh) asserts output
invariance across 38 categories of hostile input on every commit, and CodeQL
runs `security-extended` against the source weekly.

| Asset | Threat | Assessment |
|---|---|---|
| The string | Disclosure | It is a greeting. It is in the README. |
| Exit status | Tampering | Requires code execution; an attacker with that has better options |
| Availability | Denial of service | Achievable by not running the program |
| Output integrity | Injection | Not possible; there is no input to inject into |

## What Would Constitute a Vulnerability Here

Given the above, a genuine finding would have to be one of:

- A defect in how the six lines interact with a specific `libc`
  implementation
- A build configuration in the [Makefile](Makefile) or
  [pipeline](.github/workflows/ci.yml) that produces an unsafe binary
- A compromise of the pipeline itself — the workflows are this repository's
  only externally-sourced code, which is why
  [`dependabot.yml`](.github/dependabot.yml) tracks them
- A supply-chain issue in a published release artifact

Note that a finding in the first category is likely a defect in the toolchain
or `libc` rather than in this repository, and should be reported upstream as
well.

## The Format String

The single most important security property of the source is that the format
string is a **literal**:

```c
printf("Hello, World!\n");
```

If a format string is attacker-controlled, `%x` leaks stack contents, `%s`
dereferences arbitrary pointers, and `%n` **writes** to one — converting a
printing function into an arbitrary memory write and from there into code
execution. This is CWE-134, and it was the basis of a large family of remote
exploits from the late 1990s onward.

The pipeline compiles with `-Wformat=2 -Wformat-security -Wformat-nonliteral
-Werror` on every commit specifically so that a non-literal format string
cannot be introduced without failing the build.
[`tests/02-input-immunity.sh`](tests/02-input-immunity.sh) additionally passes
`%n`, `%p %p %p`, and `AAAA%08x.%08x.%n` as `argv` and asserts the output does
not change.

## Trusting the Compiler

[README section 9.5](README.md#95-supply-chain) discusses Ken Thompson's 1984
Turing Award lecture, *Reflections on Trusting Trust*, which demonstrates that
reading source code cannot tell you what a compiled binary does. This applies
here as it does everywhere, and it is the reason
[INSTALL.md section 8.2](INSTALL.md#82-prefer-building-from-source)
recommends building from source rather than downloading a binary: it reduces
the set of parties you must trust from two to one.

## Out of Scope

- Reports that the program prints a greeting. That is its function.
- Reports that the program ignores `--help`. See
  [README section 7](README.md#7-configuration).
- Automated scanner output with no accompanying analysis.
