## What this changes

<!-- One sentence. -->

## Category

- [ ] Documentation correction (factual error, with a source)
- [ ] Portability fix for a platform listed as *expected* in README section 10.1
- [ ] Typo
- [ ] Pipeline change
- [ ] Something else (see README section 15.2 first)

## Verification

- [ ] `make lint` passes
- [ ] `make test` passes (all five suites)
- [ ] `make matrix` passes
- [ ] The program still prints `Hello, World!` and exits 0

## If this changes `hello.c`

- [ ] The file still builds clean under `-std=c89` through `-std=c23` with `-Wall -Wextra -pedantic -Werror`
- [ ] The file still builds as C++
- [ ] Block comment delimiters remain balanced
- [ ] The source contains no non-ASCII bytes
- [ ] `tests/05-docs.sh` passes, meaning every line count and ratio stated in the documentation still matches the repository

## If this changes a documented figure

`tests/05-docs.sh` computes the repository's real figures and asserts the
prose against them. If it fails, update the prose rather than the test.

## Notes

<!-- Anything a reviewer should know. -->
