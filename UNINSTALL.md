# UNINSTALL

Complete removal instructions for `hello`.

**The short version:**

```bash
sudo make uninstall
```

Or, if you no longer have the source tree:

```bash
sudo rm -f /usr/local/bin/hello /usr/local/share/man/man1/hello.1
sudo rm -rf /usr/local/share/doc/hello
```

That is everything. This document explains why that claim can be made with
confidence, how to verify it, and what to do in the less straightforward
cases.

---

## Table of Contents

1. [Why This Document Is Short](#1-why-this-document-is-short)
2. [Method A: Using the Makefile](#2-method-a-using-the-makefile)
3. [Method B: By Hand](#3-method-b-by-hand)
4. [Method C: Package Managers](#4-method-c-package-managers)
5. [Verifying Complete Removal](#5-verifying-complete-removal)
6. [The Complete File Inventory](#6-the-complete-file-inventory)
7. [Build Artifacts and the Source Tree](#7-build-artifacts-and-the-source-tree)
8. [Removing a Committed Binary from Git](#8-removing-a-committed-binary-from-git)
9. [Removing the Toolchain](#9-removing-the-toolchain)
10. [Troubleshooting](#10-troubleshooting)
11. [Reinstalling](#11-reinstalling)

---

## 1. Why This Document Is Short

Most uninstall instructions are incomplete, and they are incomplete for a
structural reason: the software installed things it did not enumerate.
Configuration written on first run. A cache directory created lazily. A state
file under `~/.local/share`. A line appended to a shell profile. A systemd
unit. A cron entry. A registry key. A user account. A lockfile in `/var/run`.
An entry in another program's plugin directory.

None of that applies here, and the reason is
[INSTALL.md section 15](INSTALL.md#15-what-installation-does-not-do):
installation copies files and does nothing else. The program never writes to
disk, never reads configuration, never creates state, and never modifies
anything outside the paths `make install` explicitly placed.

A program that installs only files it can enumerate can be removed exactly.
This document is therefore complete rather than approximate, and section 5
lets you confirm that for yourself rather than take it on trust.

---

## 2. Method A: Using the Makefile

From the source tree, **with the same variables you installed with**:

```bash
sudo make uninstall
```

If you installed to a non-default prefix, pass the same one:

```bash
sudo make uninstall PREFIX=/opt/hello
make uninstall PREFIX="$HOME/.local"
```

**This is the most common uninstall error.** `make uninstall` removes exactly
the paths that `make install` would create under the variables it is given.
Running it with a different `PREFIX` than you installed with removes nothing
and reports success, because every `rm -f` succeeds against a nonexistent
file. If you are unsure what prefix you used:

```bash
command -v hello
```

The directory containing the result is your `BINDIR`; its parent is your
`PREFIX`.

### 2.1 What the target does

```make
uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)
	rm -f $(DESTDIR)$(MANDIR)/man1/$(MAN1)
	rm -f $(DESTDIR)$(DOCDIR)/README.md
	rm -f $(DESTDIR)$(DOCDIR)/INSTRUCTIONS.md
	rm -f $(DESTDIR)$(DOCDIR)/LICENSE
	-rmdir $(DESTDIR)$(DOCDIR) 2>/dev/null
```

Five named files, then a non-recursive `rmdir` of the documentation
directory.

Note that it is `rmdir` and not `rm -rf`. `rmdir` removes a directory only if
it is empty, so if you or another package placed something in
`$DOCDIR`, it survives and the command fails harmlessly — the leading `-`
tells make to ignore that failure. An uninstall target that runs `rm -rf` on a
directory it does not exclusively own is a bug waiting for the day someone
sets `DOCDIR=/usr/share/doc`.

---

## 3. Method B: By Hand

If the source tree is gone, remove the files directly. Default prefix:

```bash
sudo rm -f /usr/local/bin/hello
sudo rm -f /usr/local/share/man/man1/hello.1
sudo rm -rf /usr/local/share/doc/hello
```

Per-user installation:

```bash
rm -f ~/.local/bin/hello
rm -f ~/.local/share/man/man1/hello.1
rm -rf ~/.local/share/doc/hello
```

`/opt` installation:

```bash
sudo rm -rf /opt/hello
```

### 3.1 Finding it if you do not know where it is

```bash
command -v hello                 # the one that would run
type -a hello                    # every one on PATH
find / -name hello -type f 2>/dev/null | head
```

The last command will take a while and will find GNU Hello as well if it is
installed. To tell them apart:

```bash
/path/to/hello --version
```

GNU Hello prints a version string. This program prints `Hello, World!`,
because it ignores its arguments.

**Do not remove a `hello` you did not install.** GNU Hello is packaged by most
distributions, occupies `/usr/bin/hello`, and may be a dependency of something
else. If the file is under `/usr/bin` rather than `/usr/local/bin`, it is
almost certainly owned by your package manager — see section 4.

---

## 4. Method C: Package Managers

If you installed via a package rather than from source, use the package
manager. Removing packaged files by hand leaves the package database claiming
they exist, which breaks the next upgrade.

| System | Remove | Remove including configuration |
|---|---|---|
| Debian / Ubuntu | `sudo apt remove hello` | `sudo apt purge hello` |
| Fedora / RHEL | `sudo dnf remove hello` | — |
| Arch | `sudo pacman -R hello` | `sudo pacman -Rns hello` |
| openSUSE | `sudo zypper remove hello` | — |
| Alpine | `sudo apk del hello` | — |
| Homebrew | `brew uninstall hello` | `brew uninstall --zap hello` |
| Nix | `nix-env -e hello` | — |
| FreeBSD | `sudo pkg delete hello` | — |

The "including configuration" column is not applicable to this program, which
has none. It is listed because the distinction matters for nearly everything
else and its absence here is the point.

### 4.1 Checking whether a package owns the file

```bash
# Debian / Ubuntu
dpkg -S /usr/bin/hello

# Fedora / RHEL
rpm -qf /usr/bin/hello

# Arch
pacman -Qo /usr/bin/hello
```

If one of these names a package, do not delete the file by hand.

---

## 5. Verifying Complete Removal

```bash
command -v hello || echo "not on PATH"
man hello 2>&1 | head -1
ls /usr/local/share/doc/hello 2>&1
```

Expected: `not on PATH`, `No manual entry for hello`, and
`No such file or directory`.

### 5.1 A thorough sweep

To confirm nothing was missed anywhere on the system:

```bash
find / \( -name 'hello' -o -name 'hello.1' -o -path '*/doc/hello*' \) \
     2>/dev/null | grep -v '/proc/' | head -20
```

Anything this finds is either GNU Hello, a source tree you still have, or an
installation under a prefix you forgot. It will not find configuration, cache,
or state files, because none are ever created.

### 5.2 Places it is worth confirming nothing was left

These are the locations comparable software leaves residue in. Every one of
them should be empty of anything related to this program:

```bash
ls ~/.config/hello        2>&1   # No such file or directory
ls ~/.local/share/hello   2>&1   # No such file or directory
ls ~/.cache/hello         2>&1   # No such file or directory
ls /etc/hello*            2>&1   # No such file or directory
ls /var/lib/hello         2>&1   # No such file or directory
ls /var/log/hello*        2>&1   # No such file or directory
grep -c hello ~/.bashrc ~/.zshrc 2>/dev/null   # 0
systemctl list-unit-files 2>/dev/null | grep hello   # nothing
crontab -l 2>/dev/null | grep hello                  # nothing
```

Every one of those should come back empty. If any does not, something other
than this program put it there.

---

## 6. The Complete File Inventory

Every path this software can ever occupy, exhaustively:

| Path | Placed by | Removed by |
|---|---|---|
| `$BINDIR/hello` | `make install` | `make uninstall` |
| `$MANDIR/man1/hello.1` | `make install` | `make uninstall` |
| `$DOCDIR/README.md` | `make install` | `make uninstall` |
| `$DOCDIR/INSTRUCTIONS.md` | `make install` | `make uninstall` |
| `$DOCDIR/LICENSE` | `make install` | `make uninstall` |

Five files. There is no sixth.

This inventory is not a summary or a best effort; it is the complete literal
contents of the `install` target in the [Makefile](Makefile), which you can
read in fourteen lines and verify against a staged install:

```bash
make install DESTDIR=/tmp/verify PREFIX=/usr
find /tmp/verify -type f
rm -rf /tmp/verify
```

That command installs into a throwaway directory and lists exactly what was
placed, without touching your system. If the output has more than five lines,
this document is wrong and that is a bug worth reporting.

---

## 7. Build Artifacts and the Source Tree

Uninstalling removes the *installed* files. The source tree is separate.

### 7.1 Clean the build products

```bash
make clean
```

Removes `hello`, `hello-asan`, `hello.o`, `hello.s`, `a.out`,
`hello-src.tar.gz`, and any `.dSYM` bundles. All of these are excluded from
version control by [`.gitignore`](.gitignore), whose coverage is verified
against a real build on every commit by
[`tests/06-repository.sh`](tests/06-repository.sh).

### 7.2 Remove the source tree

```bash
cd ..
rm -rf hello
```

Nothing outside that directory is affected, because nothing was ever written
outside it.

### 7.3 What the test suites leave behind

Nothing. Every suite creates its scratch files under `mktemp -d` and removes
them via a `trap` on `EXIT`, `INT`, and `TERM`, so an interrupted test run
cleans up after itself as well as a completed one.

The single exception is deliberate: `tests/06-repository.sh` performs a real
build in the source tree in order to check that `.gitignore` covers whatever
appears. `make clean` removes the result.

---

## 8. Removing a Committed Binary from Git

If a compiled binary was committed before [`.gitignore`](.gitignore) existed,
deleting it is not enough. Git stores history, not state: a file deleted in a
later commit remains in every earlier one, and in every clone, forever.

### 8.1 Stop tracking it, keeping the file on disk

```bash
git rm --cached hello
git commit -m "Stop tracking the compiled binary"
```

This is sufficient for most purposes. The binary disappears from future
commits and remains in history.

### 8.2 Find anything else that should not be tracked

```bash
git ls-files | xargs file | grep -i executable
```

CI asserts this returns nothing on every commit; see the `lint` job in
[`.github/workflows/ci.yml`](.github/workflows/ci.yml).

### 8.3 Erasing it from history entirely

This rewrites every commit that contains the file, changing every subsequent
commit hash and requiring every collaborator to re-clone.

```bash
# git-filter-repo, the current recommended tool
git filter-repo --path hello --invert-paths
```

**For a 33 KB binary this is disproportionate.** For a leaked credential it is
mandatory — and still insufficient, because the credential must be treated as
compromised regardless of whether the history was rewritten. Anyone who cloned
the repository before the rewrite still has it.

---

## 9. Removing the Toolchain

If you installed a compiler solely to build this program and want it gone —
[INSTRUCTIONS.md Part 7](INSTRUCTIONS.md#part-7-installing-a-compiler) is what
put it there:

```bash
# Debian / Ubuntu
sudo apt remove build-essential && sudo apt autoremove

# Fedora
sudo dnf remove gcc

# Arch
sudo pacman -Rns base-devel

# macOS Command Line Tools
sudo rm -rf /Library/Developer/CommandLineTools
```

**Consider not doing this.** A C compiler is a dependency of a great deal of
software that does not announce it: Python packages with native extensions,
Ruby gems, Node modules with bindings, and most things installed from source.
Removing `build-essential` on a Debian system frequently breaks unrelated
tooling in ways that are diagnosed hours later.

The compiler occupies a few hundred megabytes and costs nothing to leave
installed.

---

## 10. Troubleshooting

| Symptom | Cause | Fix |
|---|---|---|
| `make uninstall` reports success but `hello` still runs | Wrong `PREFIX` — see section 2 | `command -v hello`, then re-run with the correct prefix |
| `Permission denied` | `$BINDIR` needs privileges | Prefix the command with `sudo`, or you installed per-user and do not need it |
| `hello` still runs after removal | Shell has cached the path | `hash -r` (bash) or `rehash` (zsh), or open a new shell |
| Removed it but `man hello` still works | `man` database is cached | `sudo mandb` on Linux, or ignore it; it self-corrects |
| A different `hello` remains | GNU Hello is installed | Section 3.1 |
| `rmdir: Directory not empty` | Something else uses `$DOCDIR` | Harmless and expected. Section 2.1. |
| Package manager reports the file is missing | Removed by hand instead of via the package | `sudo apt install --reinstall hello`, then remove properly |

---

## 11. Reinstalling

```bash
make && sudo make install
```

There is no state to restore, no configuration to migrate, and no history to
lose, because none of it ever existed. A reinstall is indistinguishable from
a first installation, which is a property worth more than it sounds.

---

**See also:** [INSTALL.md](INSTALL.md) ·
[README.md](README.md) ·
[.gitignore](.gitignore) ·
[Makefile](Makefile)
