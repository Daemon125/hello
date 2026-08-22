# Contributing

Thank you for considering a contribution.

This project is unusual in one respect that shapes everything below: **the
program is finished.** It has been feature-complete since 1972, it has no
open defects other than the one documented in
[README section 12.2](README.md#122-the-return-value-of-printf-is-not-checked),
and it cannot regress. Contributions are therefore almost entirely to the
documentation and the pipeline around it.

---

## Quick start

```bash
git clone <this repository>
cd hello
make            # build
make test       # 6 suites, 200+ assertions
make lint       # whitespace, encoding, YAML, shell syntax
make matrix     # every standard × every optimization level
```

All four must pass before you open a pull request. CI runs considerably more
(see [README section 11.7](README.md#117-continuous-integration)), but these
four catch nearly everything locally in under a minute.

---

## What will be accepted

**Documentation corrections**, with a source. This is the most likely
contribution to be merged. The documentation makes a large number of
historical, linguistic, and technical claims and some of them are wrong. Use
the [documentation issue template](.github/ISSUE_TEMPLATE/documentation.yml)
or open a pull request directly.

**Portability fixes** for a platform listed as *expected* rather than
*verified* in [README section 10.1](README.md#101-verified-platforms).

**Pipeline improvements** — a check that would catch a real class of
regression, a fix for a job that is passing for the wrong reason, a
platform-specific bug in a test script.

**Typos.**

## What will not be accepted

**Features.** [README section 3.1](README.md#31-non-features) lists what has
been considered and rejected, and section 13 explains why there is no 2.0. The
short version: the program's value is that it has nothing to get wrong, and
every feature removes some of that. If you want to make the case anyway, the
[feature request template](.github/ISSUE_TEMPLATE/feature_request.yml) asks
the two questions that matter.

**Reformatting** of the source commentary, or removing it.

**Expansions** to the source commentary. Volumes I through III are considered
complete; corrections are welcome, additions are not.

**Reflowing the Markdown.** All documents are hard-wrapped at 79 columns. A
pull request that rewraps a file produces a diff nobody can review.

---

## Development setup

No setup is required beyond a C compiler. There is no dependency to install,
no virtual environment, no container, and no configuration.

Optional tools that make `make analyze` and `make test` more thorough:

| Tool | Provides | Install |
|---|---|---|
| `valgrind` | Memory error and leak detection | `apt install valgrind` |
| `cppcheck` | Static analysis | `apt install cppcheck` |
| `clang-tidy` | Static analysis | `apt install clang-tidy` |
| `shellcheck` | Shell script linting (CI runs this) | `apt install shellcheck` |
| `mandoc` | Manual page linting | `apt install mandoc` |

Every suite skips gracefully when a tool is absent, so none are required.

---

## The rule that catches most contributors

**The documentation is tested.**

[`tests/05-docs.sh`](tests/05-docs.sh) computes the repository's real figures
— total lines, significant lines, the documentation-to-code ratio, the exact
program output, the byte count — and asserts the prose against them. If you
change the size of `hello.c` by so much as a line, the build goes red until
the figures in [README.md](README.md) and [INSTRUCTIONS.md](INSTRUCTIONS.md)
are updated to match.

The same suite extracts the test script printed in README section 11.2 and
runs it, and verifies that every internal link and every cross-reference to a
numbered section of `hello.c` resolves.

**When it fails, update the prose. Do not update the test.** The test computes
ground truth; the prose asserts it. If they disagree, the prose is wrong.

Similarly, [`tests/06-repository.sh`](tests/06-repository.sh) performs a real
build and asserts that [`.gitignore`](.gitignore) excludes everything that
appeared. A new build artifact needs a corresponding entry.

---

## Style

**C.** Match the surrounding code, which is unusually easy here. Four-space
indentation, no tabs, 79 columns, pure 7-bit ASCII. The last of these is
enforced: a non-ASCII byte in `hello.c` fails `make lint`.

**Shell.** POSIX `sh`, not bash. The suites must run on any platform the
program builds on, which includes systems without bash. No `[[ ]]`, no
`local`, no arrays, no `echo -e`. CI runs `shellcheck --shell=sh
--severity=warning` and treats findings as failures.

**Markdown.** Hard-wrapped at 79 columns. Reference sections by number, and
link them, so that [`tests/links.py`](tests/links.py) can verify them.

**Everything.** [`.editorconfig`](.editorconfig) encodes the above. `make
lint` enforces trailing whitespace and final newlines directly rather than
trusting that your editor honoured it.

---

## Commit messages

```
subject in the imperative, under 72 characters

Body explaining why, wrapped at 72 columns. What changed is visible in the
diff; why it changed is not, and is the thing a reader in three years will
need.

Refs #123
```

Prefix pipeline-only changes with `ci:`, matching the convention
[`dependabot.yml`](.github/dependabot.yml) uses for its own pull requests.

---

## Pull requests

1. Branch from `master`.
2. Make the change.
3. Run `make lint && make test && make matrix`.
4. If you changed `hello.c`'s size, update the figures the docs suite checks.
5. Open the pull request. The
   [template](.github/PULL_REQUEST_TEMPLATE.md) has the checklist.

CI will run roughly 100 jobs across three operating systems and five
architectures. All must pass. If a job fails on a platform you cannot
reproduce on, say so in the pull request rather than guessing — several
already-fixed bugs in this repository were platform-specific:
BSD `sed` lacking `\|` alternation, LeakSanitizer being absent on macOS, and
Apple's linker embedding a fresh `LC_UUID` in every image.

---

## Reporting rather than fixing

A well-described issue is a real contribution. See
[SUPPORT.md](SUPPORT.md) for where to file what, and include the output of
`./hello | od -c` — byte-level output makes visible the trailing whitespace,
missing newlines, and CRLF endings that a screenshot hides.

Security issues go through [SECURITY.md](SECURITY.md), never a public issue.

---

## Code of Conduct

The [Code of Conduct](CODE_OF_CONDUCT.md) is short: be civil, assume
competence, criticise the work rather than the person. Note in particular its
project-specific clause — this repository's documentation is aimed partly at
people writing their first program, and condescension toward beginners is out
of place here.
