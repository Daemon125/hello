# Changelog

All notable changes to this project are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

Note that the program's observable behaviour has not changed since 1972.
Every entry below 1.1.0 records a change forced by the language evolving
underneath it; every entry from 1.1.0 onward records documentation and
infrastructure. There has never been a bug fix, because there has never been
a bug in the six lines.

---

## [Unreleased]

Nothing.

## [1.2.0] — 2026-08-22

### Added

- Continuous integration (`.github/workflows/ci.yml`), 12 jobs expanding to
  roughly 100 across 3 operating systems, 5 architectures, 4 language
  standards, and 6 sanitizers
- CodeQL scanning with `security-extended`, weekly
- A nightly workflow rebuilding unchanged source against pre-release
  toolchains, on the reasoning that the source is the control and the
  toolchain is the variable
- Seven test suites in `tests/`, totalling over 250 assertions
- `tests/05-docs.sh`, which computes the repository's real figures and fails
  the build when the documentation disagrees with them
- `tests/06-repository.sh`, which verifies `.gitignore` coverage against a
  real build rather than assuming it
- `Makefile`, with `install`, `uninstall`, and `installcheck` targets
  following the GNU conventions for `PREFIX` and `DESTDIR`
- `hello.1`, a manual page, lint-clean under `mandoc -Tlint`
- `.gitignore`, 25 build-product patterns, coverage verified on every commit
- `INSTALL.md` and `UNINSTALL.md`
- `CONTRIBUTING.md`, `SECURITY.md`, `SUPPORT.md`, `CODE_OF_CONDUCT.md`
- `LICENSE` (Unlicense), `CITATION.cff`, `.editorconfig`
- Issue templates for bug reports, documentation corrections, and feature
  requests; a pull request template; Dependabot for the workflows

### Fixed

- Corrected the stated line counts and documentation-to-code ratio, which the
  new documentation suite found to be wrong on its first run: 7 lines of code
  became 6, 2,708 lines of commentary became 2,712, and the ratio 387:1
  became 452:1
- `README.md` skipped section 11.9 entirely: a section inserted immediately
  before an existing one, with the existing one renumbered out of the way,
  left 11.8 followed by 11.10. Now checked by `tests/sections.py`.
- `make help` printed a hardcoded line range and began leaking variable
  definitions when the comment header grew. Now derived from the file.
- A check comparing documented Makefile targets against declared ones used
  bash process substitution in a POSIX `sh` script; the substitution errored,
  the result was empty, and both assertions passed vacuously
- Reproducibility test compared two binaries built to different output paths,
  and reported nondeterminism that did not exist — some toolchains embed the
  output filename in the debug map. Now builds twice to a single path.
- `make sanitize` aborted on macOS, where LeakSanitizer is not implemented in
  Apple's ASan runtime and `detect_leaks=1` is a hard failure rather than a
  warning
- Fenced-block extraction in `tests/05-docs.sh` used `\|` alternation, which
  BSD `sed` does not support, and failed silently on macOS
- Test helpers truncated the file they were testing, so every assertion after
  `.gitignore` was checked against an empty file and passed for the wrong
  reason
- Quoting throughout the Makefile and test runner, which broke when the
  repository path contained a space
- Failure summaries printed literal `\n` rather than newlines

### Changed

- No functional change. The program is byte-identical to 1.1.0.

## [1.1.0] — 2026-08-22

### Added

- A three-volume treatment in the source commentary, 2,712 lines: the descent
  of the sentence from Proto-Indo-European, the descent of the machine from
  ALGOL 60, and the philosophical status of the utterance
- `README.md` and `INSTRUCTIONS.md`

### Changed

- No functional change.

## [1.0.2] — 1999

### Changed

- Added an explicit `int` return type to `main`. C99 removed implicit `int`.
- Added an explicit `return 0;`. Optional under C99, written out because
  relying on the implicit return requires the reader to know a rule most
  readers do not know.

## [1.0.1] — 1989

### Fixed

- Added `#include <stdio.h>`. C89 requires a visible prototype for a variadic
  function; calling `printf` without one had been undefined behaviour since
  the standard said so.

## [1.0.0] — 1972

### Added

- Initial release, in Brian Kernighan's *A Tutorial Introduction to the
  Language B*, Bell Laboratories.
- Prints `hello, world`. Lowercase, no exclamation point.

---

[Unreleased]: https://github.com/Daemon125/hello/compare/v1.2.0...HEAD
[1.2.0]: https://github.com/Daemon125/hello/releases/tag/v1.2.0

Entries before 1.2.0 predate this repository and have no corresponding tag.
1.0.0 through 1.0.2 record changes the C standard forced on the program
between 1972 and 1999; 1.1.0 records the commentary, which was written
alongside 1.2.0 and released with it.
