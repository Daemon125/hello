# Build and verification for hello.
#
# The program itself needs no build system; `cc -o hello hello.c` is
# sufficient and is what INSTRUCTIONS.md tells a first-time reader to type.
# This Makefile exists for the verification around it -- the test suites,
# the analysers, and the artifacts CI produces -- so that the same commands
# run locally and in the pipeline, and neither can drift from the other.
#
# Targets:
#   all          build the program (default)
#   install      install binary, manual page, and docs (PREFIX, DESTDIR)
#   install-strip  install, then strip the binary's symbol table
#   uninstall    remove what install placed
#   installcheck verify an installation rather than a build tree
#   man          lint and preview the manual page
#   test         build and run the full test suite
#   lint         whitespace, encoding, and hygiene checks
#   analyze      static analysis (cppcheck, clang-tidy, gcc -fanalyzer)
#   sanitize     build and run under ASan and UBSan
#   valgrind     run under valgrind, if installed
#   bench        time the program against its documented figures
#   matrix       build under every standard and optimization level
#   stats        print the repository's quantitative claims
#   dist         produce a source tarball
#   clean        remove all build products
#   help         print this list

CC      ?= cc
CFLAGS  ?= -std=c99 -O2
WARN     = -Wall -Wextra -pedantic
STRICT   = $(WARN) -Werror
TARGET   = hello
SRC      = hello.c
MAN1     = hello.1

# GNU installation conventions. PREFIX selects the installation root;
# DESTDIR prepends a staging directory without affecting paths compiled
# into the program -- which matters not at all here, since nothing is
# compiled in, but package builders expect it and its absence breaks them.
PREFIX  ?= /usr/local
BINDIR  ?= $(PREFIX)/bin
DATADIR ?= $(PREFIX)/share
MANDIR  ?= $(DATADIR)/man
DOCDIR  ?= $(DATADIR)/doc/hello
DESTDIR ?=
INSTALL ?= install

.POSIX:
.PHONY: all test lint analyze sanitize valgrind bench matrix stats dist clean help
.PHONY: install uninstall install-strip installcheck man

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(STRICT) -o $@ $<

# ------------------------------------------------------------ installation

# Installs two files: the binary and its manual page. Nothing else. There
# is no configuration to place, no state directory to create, no service
# to register, and no post-install script. See INSTALL.md section 2.
install: $(TARGET)
	$(INSTALL) -d $(DESTDIR)$(BINDIR)
	$(INSTALL) -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)
	$(INSTALL) -d $(DESTDIR)$(MANDIR)/man1
	$(INSTALL) -m 644 $(MAN1) $(DESTDIR)$(MANDIR)/man1/$(MAN1)
	$(INSTALL) -d $(DESTDIR)$(DOCDIR)
	$(INSTALL) -m 644 README.md INSTRUCTIONS.md LICENSE $(DESTDIR)$(DOCDIR)/
	@echo "installed:"
	@echo "  $(DESTDIR)$(BINDIR)/$(TARGET)"
	@echo "  $(DESTDIR)$(MANDIR)/man1/$(MAN1)"
	@echo "  $(DESTDIR)$(DOCDIR)/"
	@echo "to remove, run 'make uninstall' with the same PREFIX. See UNINSTALL.md."

install-strip: install
	strip $(DESTDIR)$(BINDIR)/$(TARGET) 2>/dev/null || true

# Removes exactly what install placed, and the doc directory if it is
# empty afterwards. Never recursive; see UNINSTALL.md section 6.
uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)
	rm -f $(DESTDIR)$(MANDIR)/man1/$(MAN1)
	rm -f $(DESTDIR)$(DOCDIR)/README.md
	rm -f $(DESTDIR)$(DOCDIR)/INSTRUCTIONS.md
	rm -f $(DESTDIR)$(DOCDIR)/LICENSE
	-rmdir $(DESTDIR)$(DOCDIR) 2>/dev/null
	@echo "removed. Verify with: command -v hello || echo 'not on PATH'"

# Verifies an installation rather than a build tree, as required by the
# GNU standards. Runs against the installed binary, not ./hello.
installcheck:
	@test -x $(DESTDIR)$(BINDIR)/$(TARGET) \
	  || (echo "FAIL: $(DESTDIR)$(BINDIR)/$(TARGET) is not executable" && exit 1)
	@test "$$($(DESTDIR)$(BINDIR)/$(TARGET))" = "Hello, World!" \
	  || (echo "FAIL: installed binary produced wrong output" && exit 1)
	@man -M $(DESTDIR)$(MANDIR) 1 $(TARGET) > /dev/null 2>&1 \
	  || (echo "FAIL: manual page not installed or not renderable" && exit 1)
	@BIN=$(DESTDIR)$(BINDIR)/$(TARGET) sh tests/01-behavior.sh > /dev/null \
	  || (echo "FAIL: installed binary failed the behaviour suite" && exit 1)
	@echo "installcheck: binary, manual page, and behaviour suite all verified"

man:
	@command -v mandoc >/dev/null 2>&1 && mandoc -Tlint $(MAN1) && echo "  $(MAN1) lints clean" \
	  || echo "  (mandoc not installed; skipping lint)"
	@man ./$(MAN1) | head -5

# ---------------------------------------------------------------- testing

test: $(TARGET)
	@BIN="$(CURDIR)/$(TARGET)" CC="$(CC)" sh tests/run.sh

lint:
	@echo "== trailing whitespace =="
	@! grep -rn '[[:space:]]$$' --include='*.c' --include='*.md' --include='*.sh' \
	       --include='*.yml' --include='*.py' . \
	  || (echo "FAIL: trailing whitespace" && exit 1)
	@echo "  none"
	@echo "== tabs in C source =="
	@! grep -Pn '\t' $(SRC) 2>/dev/null || true
	@echo "== non-ASCII bytes in C source =="
	@! LC_ALL=C grep -n '[^\t -~]' $(SRC) \
	  || (echo "FAIL: non-ASCII byte in source" && exit 1)
	@echo "  none"
	@echo "== shell script syntax =="
	@for f in tests/*.sh; do sh -n "$$f" || exit 1; done
	@echo "  all scripts parse"
	@echo "== shellcheck =="
	@# Run with the same flags CI uses. `sh -n` above only checks that the
	@# script parses; it says nothing about POSIX conformance, and the
	@# suites must run on shells that are not bash. Discovering that in CI
	@# costs a full matrix run.
	@if command -v shellcheck >/dev/null 2>&1; then \
	  shellcheck --shell=sh --severity=warning tests/*.sh || exit 1; \
	  echo "  all scripts pass shellcheck"; \
	else \
	  echo "  (shellcheck not installed locally; CI runs it)"; \
	fi
	@echo "== workflow YAML =="
	@if python3 -c 'import yaml' 2>/dev/null; then \
	  python3 -c "import yaml,glob; [yaml.safe_load(open(f)) for f in \
	    glob.glob('.github/**/*.yml', recursive=True)]" || exit 1; \
	  echo "  all workflows parse"; \
	else \
	  echo "  (PyYAML not installed; actionlint below covers this)"; \
	fi
	@echo "== regex portability =="
	@# GNU and BSD grep disagree about backslash escapes, and the suites
	@# must produce the same result under both. Three defects of this exact
	@# shape reached CI before this check existed: `^\t` (BSD reads a tab,
	@# GNU reads the letter t), `[^\t -~]` (the disagreement runs the other
	@# way inside a bracket), and `\\\`` (GNU reads its start-of-buffer
	@# anchor). Use awk, or a fixed-string grep -F, instead.
	@# The `:[0-9]*:[[:space:]]*#` filter drops comment lines. grep -n emits
	@# `file:line:content`, so a pattern anchored with ^ can never match the
	@# content -- an earlier version of this rule used `^\s*#` and flagged
	@# the comments that explain the rule.
	@if grep -n "grep[^|]*\\\\[t\\\`]" tests/*.sh \
	   | grep -v ':[0-9]*:[[:space:]]*#'; then \
	  echo "  FAIL: backslash escape inside a grep pattern; see the comment in the Makefile"; \
	  exit 1; \
	else \
	  echo "  no backslash escapes inside grep patterns"; \
	fi
	@echo "== workflow schema and expressions =="
	@# Parsing as YAML is necessary and not sufficient. GitHub Actions
	@# expressions have their own grammar -- string literals accept single
	@# quotes only -- and a violation makes the whole file unloadable, which
	@# surfaces as a run that fails in 0s with no jobs and no useful error.
	@# actionlint checks the workflow schema, expression syntax, runner
	@# labels, and shellcheck for every run: block.
	@if command -v actionlint >/dev/null 2>&1; then \
	  actionlint || exit 1; \
	  echo "  all workflows pass actionlint"; \
	else \
	  echo "  (actionlint not installed locally; CI runs it)"; \
	fi
	@echo "== final newline =="
	@for f in $(SRC) README.md INSTRUCTIONS.md Makefile; do \
	  [ -z "$$(tail -c1 $$f)" ] || (echo "FAIL: $$f lacks a final newline" && exit 1); \
	done
	@echo "  all files terminated"

# ------------------------------------------------------------- analysis

analyze:
	@echo "== gcc -fanalyzer =="
	@$(CC) -fanalyzer $(WARN) -c -o /dev/null $(SRC) 2>&1 \
	  || echo "  (analyzer unavailable on this compiler)"
	@echo "== cppcheck =="
	@command -v cppcheck >/dev/null 2>&1 \
	  && cppcheck --enable=all --inconclusive --std=c99 \
	              --suppress=missingIncludeSystem \
	              --error-exitcode=1 $(SRC) \
	  || echo "  (cppcheck not installed)"
	@echo "== clang-tidy =="
	@command -v clang-tidy >/dev/null 2>&1 \
	  && clang-tidy $(SRC) --warnings-as-errors='*' -- -std=c99 \
	  || echo "  (clang-tidy not installed)"

sanitize:
	@echo "== AddressSanitizer + UndefinedBehaviorSanitizer =="
	$(CC) -std=c99 -O1 -g $(WARN) -fsanitize=address,undefined \
	      -fno-omit-frame-pointer -o $(TARGET)-asan $(SRC)
	@# LeakSanitizer is not implemented in Apple's ASan runtime, and asking
	@# for it there is a hard abort rather than a warning. Enabled only
	@# where the platform supports it.
	@case "$$(uname -s)" in \
	  Linux) leaks=1 ;; \
	  *)     leaks=0 ;; \
	esac; \
	ASAN_OPTIONS=detect_leaks=$$leaks UBSAN_OPTIONS=halt_on_error=1 \
	  ./$(TARGET)-asan
	@echo "  clean under ASan + UBSan"

valgrind: $(TARGET)
	@command -v valgrind >/dev/null 2>&1 \
	  && valgrind --leak-check=full --show-leak-kinds=all \
	              --track-origins=yes --error-exitcode=1 ./$(TARGET) \
	  || echo "  (valgrind not installed)"

# ------------------------------------------------------------ inspection

bench: $(TARGET)
	@echo "== 1000 invocations =="
	@start=$$(date +%s); \
	 i=0; while [ $$i -lt 1000 ]; do ./$(TARGET) >/dev/null; i=$$((i+1)); done; \
	 end=$$(date +%s); \
	 echo "  elapsed: $$((end - start))s for 1000 runs (process spawn dominated)"
	@echo "  see README section 8.1: ~99.75% of runtime is outside the program"

matrix:
	@for std in c89 c99 c11 c17; do \
	  for opt in -O0 -O2 -Os; do \
	    printf '  %-8s %-4s ' "$$std" "$$opt"; \
	    if $(CC) -std=$$std $$opt $(STRICT) -o /tmp/hm $(SRC) 2>/dev/null \
	       && [ "$$(/tmp/hm)" = "Hello, World!" ]; then echo "ok"; \
	    else echo "FAIL"; exit 1; fi; \
	  done; \
	done; rm -f /tmp/hm

stats:
	@total=$$(wc -l < $(SRC) | tr -d ' '); \
	 sig=$$(sed 's|/\*|\n&|g; s|\*/|&\n|g' $(SRC) \
	        | awk '/\/\*/{c=1} !c && NF {print} /\*\//{c=0}' \
	        | grep -c '[^[:space:]]' | tr -d ' '); \
	 doc=$$((total - sig)); \
	 printf '  hello.c        %6s lines  (%s significant, %s commentary)\n' "$$total" "$$sig" "$$doc"; \
	 printf '  README.md      %6s lines\n' "$$(wc -l < README.md | tr -d ' ')"; \
	 printf '  INSTRUCTIONS   %6s lines\n' "$$(wc -l < INSTRUCTIONS.md | tr -d ' ')"; \
	 printf '  ratio          %6s:1\n' "$$((doc / sig))"

dist: clean
	@tar czf hello-src.tar.gz $(SRC) $(MAN1) README.md INSTRUCTIONS.md \
	    INSTALL.md UNINSTALL.md CONTRIBUTING.md SECURITY.md CHANGELOG.md \
	    CODE_OF_CONDUCT.md SUPPORT.md LICENSE CITATION.cff \
	    Makefile .editorconfig .gitignore tests .github
	@echo "  hello-src.tar.gz ($$(wc -c < hello-src.tar.gz | tr -d ' ') bytes)"

clean:
	rm -f $(TARGET) $(TARGET)-asan $(TARGET).o $(TARGET).s a.out hello-src.tar.gz
	rm -rf *.dSYM

# Prints the file's leading comment block. Derived from the file rather than
# from a hardcoded line range: an earlier version used `sed -n '2,34p'` and
# silently began printing variable definitions when the header grew.
help:
	@awk 'NR==1 { next } /^#/ { sub(/^# ?/, ""); print; next } { exit }' Makefile
