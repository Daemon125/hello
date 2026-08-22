# INSTALL

Installation instructions for `hello`.

**If you only want to run it once, you do not need to install anything:**

```bash
cc -o hello hello.c && ./hello
```

That is the entire build. The rest of this document covers installing it
system-wide, packaging it for a distribution, verifying a release artifact,
and installing it somewhere it can be found by name.

For removal, see [UNINSTALL.md](UNINSTALL.md). For a guide that assumes you do
not yet own a computer, see [INSTRUCTIONS.md](INSTRUCTIONS.md).

---

## Table of Contents

1. [Requirements](#1-requirements)
2. [What Installation Actually Does](#2-what-installation-actually-does)
3. [Method A: Build and Install from Source](#3-method-a-build-and-install-from-source)
4. [Method B: Per-User Installation](#4-method-b-per-user-installation)
5. [Method C: Staged and Packaged Installation](#5-method-c-staged-and-packaged-installation)
6. [Method D: Distribution Packaging](#6-method-d-distribution-packaging)
7. [Method E: Container](#7-method-e-container)
8. [Method F: From a Release Artifact](#8-method-f-from-a-release-artifact)
9. [Installation Layout](#9-installation-layout)
10. [Verifying an Installation](#10-verifying-an-installation)
11. [Cross-Compilation and Sysroots](#11-cross-compilation-and-sysroots)
12. [Air-Gapped Installation](#12-air-gapped-installation)
13. [Upgrading](#13-upgrading)
14. [Troubleshooting](#14-troubleshooting)
15. [What Installation Does Not Do](#15-what-installation-does-not-do)

---

## 1. Requirements

### 1.1 Build requirements

| Requirement | Version | Notes |
|---|---|---|
| A C compiler | Anything since about 1990 | GCC, Clang, MSVC, TCC, ICC all verified |
| A hosted C library | Any | Supplies `stdio.h` and `printf` |
| `make` | Any POSIX make | **Optional.** Only needed for `make install`. |

There are no other dependencies. No package manager, no lockfile, no
transitive dependency tree, nothing to audit, and no network access required
at any point after obtaining the source.

Verify your toolchain before proceeding:

```bash
printf 'int main(void){return 0;}' > /tmp/t.c && cc -o /tmp/t /tmp/t.c && /tmp/t && echo OK
```

If that does not print `OK`, install a compiler first —
[INSTRUCTIONS.md Part 7](INSTRUCTIONS.md#part-7-installing-a-compiler) covers
every major platform.

### 1.2 Runtime requirements

| Resource | Required |
|---|---|
| Disk | 33 KB for the binary, ~4 KB for the manual page |
| Memory | ~1.5 MB resident, essentially all of it mapped `libc` |
| CPU | Any |
| Network | None, ever |
| Privileges | None to run; write access to `$BINDIR` to install |

### 1.3 Supported platforms

Verified in CI on every commit: Linux (glibc and musl), macOS, Windows (MSVC,
clang-cl, MinGW), and cross-compiled and executed under QEMU for aarch64,
armhf, riscv64, ppc64le, and s390x. See
[README section 10](README.md#10-portability).

---

## 2. What Installation Actually Does

It copies two files.

```
$PREFIX/bin/hello                    the binary        33 KB
$PREFIX/share/man/man1/hello.1       the manual page    4 KB
$PREFIX/share/doc/hello/             README, INSTRUCTIONS, LICENSE
```

That is the complete inventory. There is no configuration file to place, no
state or cache directory to create, no service or unit to register, no
scheduled task, no shell completion, no dynamic library, no post-install
script, and no daemon.

This is worth stating explicitly because it is what makes
[UNINSTALL.md](UNINSTALL.md) short and complete. A program that installs only
files it can enumerate is a program that can be removed exactly.

---

## 3. Method A: Build and Install from Source

The default installation, and the one the rest of this document assumes.

```bash
make
sudo make install
```

Default `PREFIX` is `/usr/local`, which is the correct location for software
installed by an administrator outside the system package manager. This is not
arbitrary: the Filesystem Hierarchy Standard reserves `/usr/local` for exactly
this purpose, so that a distribution upgrade will not overwrite it and a
package manager will not claim ownership of it.

### 3.1 Choosing a different prefix

```bash
sudo make install PREFIX=/opt/hello
```

`PREFIX` propagates to `BINDIR`, `MANDIR`, `DATADIR`, and `DOCDIR`. Any of
those may also be overridden individually:

```bash
sudo make install PREFIX=/usr BINDIR=/usr/bin MANDIR=/usr/share/man
```

### 3.2 Variables

| Variable | Default | Purpose |
|---|---|---|
| `PREFIX` | `/usr/local` | Installation root |
| `BINDIR` | `$(PREFIX)/bin` | Where the binary goes |
| `DATADIR` | `$(PREFIX)/share` | Architecture-independent data |
| `MANDIR` | `$(DATADIR)/man` | Manual pages; `man1/` is appended |
| `DOCDIR` | `$(DATADIR)/doc/hello` | Documentation |
| `DESTDIR` | empty | Staging root; see section 5 |
| `CC` | `cc` | Compiler |
| `CFLAGS` | `-std=c99 -O2` | Compiler flags |
| `INSTALL` | `install` | The install(1) program |

### 3.3 Stripped installation

```bash
sudo make install-strip
```

Runs `strip(1)` on the installed binary, removing the symbol table. Saves a
few kilobytes and makes a stack trace useless. For a program with one function
and no failure modes this is a reasonable trade; in general it is not.

---

## 4. Method B: Per-User Installation

No administrator privileges required, and preferable on a shared machine.

```bash
make install PREFIX="$HOME/.local"
```

This follows the XDG convention and installs to `~/.local/bin` and
`~/.local/share/man`. Most modern distributions already place `~/.local/bin`
on `PATH`.

### 4.1 If it is not on your PATH

Check first:

```bash
echo "$PATH" | tr ':' '\n' | grep -x "$HOME/.local/bin" || echo "not on PATH"
```

To add it, append the following to your shell's startup file — `~/.bashrc`
for bash, `~/.zshrc` for zsh, `~/.config/fish/config.fish` for fish:

```bash
export PATH="$HOME/.local/bin:$PATH"
```

Then start a new shell, or `source` the file. Verify:

```bash
command -v hello
```

### 4.2 If the manual page is not found

```bash
export MANPATH="$HOME/.local/share/man:$MANPATH"
```

Or read it directly without installing anything:

```bash
man ./hello.1
```

---

## 5. Method C: Staged and Packaged Installation

`DESTDIR` prepends a staging directory to every installation path without
affecting anything compiled into the program. This is the mechanism every
distribution packaging system uses: build into a clean directory, then
package that directory's contents.

```bash
make install DESTDIR=/tmp/stage PREFIX=/usr
find /tmp/stage -type f
```

Produces:

```
/tmp/stage/usr/bin/hello
/tmp/stage/usr/share/man/man1/hello.1
/tmp/stage/usr/share/doc/hello/README.md
/tmp/stage/usr/share/doc/hello/INSTRUCTIONS.md
/tmp/stage/usr/share/doc/hello/LICENSE
```

Note that `DESTDIR` is a **staging** prefix and `PREFIX` is a **real** one.
A package built with `DESTDIR=/tmp/stage PREFIX=/usr` installs to `/usr` on
the target machine. Confusing the two is the most common packaging error, and
it produces a package that installs into `/tmp/stage/usr` on the user's
system.

---

## 6. Method D: Distribution Packaging

Templates for the major systems. All five have been kept minimal
deliberately; there is nothing here that needs configuring.

### 6.1 Debian / Ubuntu

`debian/rules`:

```make
#!/usr/bin/make -f
%:
	dh $@

override_dh_auto_install:
	$(MAKE) install DESTDIR=$(CURDIR)/debian/hello PREFIX=/usr
```

`debian/control`:

```
Source: hello
Section: misc
Priority: optional
Maintainer: Nobody <nobody@example.invalid>
Build-Depends: debhelper-compat (= 13)
Standards-Version: 4.6.2

Package: hello
Architecture: any
Depends: ${shlibs:Depends}, ${misc:Depends}
Description: print a greeting to standard output
 Writes "Hello, World!" to standard output and exits. Accepts no options,
 reads no input, and retains no state.
 .
 Ships 2,712 lines of commentary on the sentence's descent from
 Proto-Indo-European, the history of C, and the philosophical status of
 the utterance.
```

Build with `dpkg-buildpackage -us -uc`.

### 6.2 RPM (Fedora, RHEL, openSUSE)

`hello.spec`:

```spec
Name:           hello
Version:        1.2.0
Release:        1%{?dist}
Summary:        Print a greeting to standard output
License:        Unlicense
URL:            https://github.com/Daemon125/hello
Source0:        %{name}-%{version}.tar.gz
BuildRequires:  gcc, make

%description
Writes "Hello, World!" to standard output and exits. Accepts no options,
reads no input, and retains no state between invocations.

%prep
%autosetup

%build
%make_build

%check
%make_build test

%install
%make_install PREFIX=%{_prefix}

%files
%{_bindir}/hello
%{_mandir}/man1/hello.1*
%doc README.md INSTRUCTIONS.md
%license LICENSE

%changelog
* Sat Aug 22 2026 Nobody <nobody@example.invalid> - 1.2.0-1
- Initial package
```

Note the `%check` section. The test suite runs at package build time, which is
where a toolchain regression on the build host would surface.

### 6.3 Arch Linux

`PKGBUILD`:

```bash
pkgname=hello
pkgver=1.2.0
pkgrel=1
pkgdesc="Print a greeting to standard output"
arch=('x86_64' 'aarch64')
license=('Unlicense')
makedepends=('gcc' 'make')
source=("$pkgname-$pkgver.tar.gz")
sha256sums=('SKIP')

build()   { cd "$pkgname-$pkgver"; make; }
check()   { cd "$pkgname-$pkgver"; make test; }
package() { cd "$pkgname-$pkgver"; make install DESTDIR="$pkgdir" PREFIX=/usr; }
```

### 6.4 Homebrew

`Formula/hello.rb`:

```ruby
class Hello < Formula
  desc "Print a greeting to standard output"
  homepage "https://github.com/Daemon125/hello"
  url "https://github.com/Daemon125/hello/archive/refs/tags/v1.2.0.tar.gz"
  license :public_domain

  def install
    system "make", "install", "PREFIX=#{prefix}"
  end

  test do
    assert_equal "Hello, World!", shell_output("#{bin}/hello").strip
  end
end
```

### 6.5 Nix

`default.nix`:

```nix
{ stdenv, lib }:

stdenv.mkDerivation {
  pname = "hello";
  version = "1.2.0";
  src = ./.;

  doCheck = true;
  checkTarget = "test";
  makeFlags = [ "PREFIX=$(out)" ];

  meta = with lib; {
    description = "Print a greeting to standard output";
    license = licenses.unlicense;
    platforms = platforms.all;
  };
}
```

Note that the upstream `nixpkgs` already contains a package named `hello`,
GNU Hello, which is a different and considerably larger program with
command-line options, internationalization, and a `--help` flag. It is
maintained by the GNU project as a demonstration of how a GNU package should
be structured, and it is roughly 4,000 lines. This is not that.

---

## 7. Method E: Container

A container for this program is four orders of magnitude larger than the
program. It is included because someone will ask.

`Dockerfile`:

```dockerfile
FROM gcc:13 AS build
WORKDIR /src
COPY hello.c .
RUN cc -std=c99 -O2 -static -Wall -Wextra -pedantic -Werror -o /hello hello.c

FROM scratch
COPY --from=build /hello /hello
ENTRYPOINT ["/hello"]
```

```bash
docker build -t hello .
docker run --rm hello
```

The static link and the `scratch` base are what make this defensible: the
final image contains exactly one file and no operating system. It is roughly
800 KB, of which the program is 33 KB and `libc` is the rest.

For a program with no dependencies, no configuration, and no network access,
containerization solves no problem that exists. Use the binary.

---

## 8. Method F: From a Release Artifact

### 8.1 Verify before you run

Never execute a downloaded binary without verifying it. This is not
boilerplate — [README section 9.5](README.md#95-supply-chain) sets out why the
source telling you what a binary does is not evidence that it does it.

```bash
# Checksum
sha256sum -c hello-1.2.0.sha256

# Signature, if one is published
gpg --verify hello-1.2.0.tar.gz.asc hello-1.2.0.tar.gz
```

A checksum published on the same server as the artifact protects against
corruption in transit, not against a compromised server. A signature verified
against a key you obtained independently protects against both.

### 8.2 Prefer building from source

For this program specifically, building from source is strictly better than
downloading a binary:

- The source is six lines and can be read in full in under a minute
- The build takes well under a second
- The result is native to your architecture
- It requires trusting only your own compiler, rather than your compiler *and*
  someone else's build machine

The only reason to install a prebuilt binary is the absence of a compiler,
and [INSTRUCTIONS.md Part 7](INSTRUCTIONS.md#part-7-installing-a-compiler)
resolves that in one command on every platform.

---

## 9. Installation Layout

### 9.1 Files placed

| Path | Mode | Size | Purpose |
|---|---|---|---|
| `$BINDIR/hello` | 755 | ~33 KB | The program |
| `$MANDIR/man1/hello.1` | 644 | ~4 KB | Manual page |
| `$DOCDIR/README.md` | 644 | ~40 KB | Technical documentation |
| `$DOCDIR/INSTRUCTIONS.md` | 644 | ~73 KB | First-time guide |
| `$DOCDIR/LICENSE` | 644 | ~2 KB | Public domain dedication |

The documentation is larger than the program by a factor of roughly 3,500.
This is the correct proportion and is discussed in
[README section 12.5](README.md#125-the-documentation-is-452-times-the-size-of-the-program).

### 9.2 Choosing a prefix

| Prefix | When |
|---|---|
| `/usr/local` | Default. Administrator-installed software outside the package manager. Safe from distribution upgrades. |
| `/usr` | Only when a distribution package manager owns the file. Installing here by hand puts you in conflict with it. |
| `~/.local` | Per-user, no privileges needed. Preferred on shared machines. |
| `/opt/hello` | Self-contained tree, easy to remove wholesale. Requires PATH and MANPATH changes. |

---

## 10. Verifying an Installation

```bash
make installcheck
```

This is the GNU-standard target for verifying an installation rather than a
build tree. It asserts that the installed binary exists and is executable,
produces the exact expected output, that the manual page was placed, and then
runs the full behaviour suite against the *installed* binary rather than
against `./hello`.

Manually:

```bash
command -v hello              # is it on PATH?
hello                         # Hello, World!
hello; echo $?                # 0
hello | wc -c                 # 14
hello | od -c                 # exact bytes
man hello                     # manual page found
```

If `command -v hello` finds nothing, the binary installed somewhere not on
your `PATH`. See section 4.1.

If it finds the *wrong* `hello` — GNU Hello is packaged by most
distributions — check which:

```bash
command -v hello
hello --version    # GNU Hello prints a version; this program prints its greeting
```

---

## 11. Cross-Compilation and Sysroots

```bash
make CC=aarch64-linux-gnu-gcc
make install DESTDIR=/path/to/target/rootfs PREFIX=/usr
```

Nothing in the build embeds a host path, so a cross-installation needs no
special handling beyond pointing `DESTDIR` at the target root.

Verify the result under emulation before deploying it:

```bash
qemu-aarch64-static ./hello
```

CI cross-compiles and executes for five architectures on every commit,
including big-endian s390x. See
[README section 11.7](README.md#117-continuous-integration).

---

## 12. Air-Gapped Installation

The complete input to a build is one file. To install on a machine with no
network access, copy `hello.c` to it by any means and run:

```bash
cc -o hello hello.c && sudo install -m 755 hello /usr/local/bin/hello
```

No dependency resolution, no lockfile, no vendored modules, no offline mirror,
and no proxy configuration. This is not a feature that was designed; it is
what the absence of dependencies gets you for free, and it is worth noticing
how rare it has become.

---

## 13. Upgrading

```bash
git pull
make clean && make && sudo make install
```

`make install` overwrites in place. There is no migration to perform, no
schema to update, no cache to invalidate, and no state to preserve, because
there is no state.

Downgrading is the same operation in reverse and is equally uneventful.

---

## 14. Troubleshooting

| Symptom | Cause | Fix |
|---|---|---|
| `make: command not found` | No `make` installed | Use `cc -o hello hello.c` directly; `make` is optional |
| `Permission denied` during install | `$BINDIR` is not writable | Use `sudo`, or install per-user (section 4) |
| `install: command not found` | BusyBox or a minimal system | `make install INSTALL="cp"` — loses mode setting, so `chmod 755` afterwards |
| `hello: command not found` after install | `$BINDIR` is not on `PATH` | Section 4.1 |
| `No manual entry for hello` | `$MANDIR` is not on `MANPATH` | Section 4.2, or `man ./hello.1` |
| Wrong `hello` runs | GNU Hello is also installed | Section 10 |
| Installed binary fails but `./hello` works | Stale install from an earlier build | `make clean && make && sudo make install` |

For build failures rather than install failures, see
[INSTRUCTIONS.md Part 15](INSTRUCTIONS.md#part-15-troubleshooting), which
covers fifteen common errors with their causes.

---

## 15. What Installation Does Not Do

Recorded explicitly, because an absence is invisible and because every item
here is something comparable software does.

- **No configuration file** is created, in `/etc`, in `~/.config`, or anywhere
  else. There is nothing to configure.
- **No state, cache, or data directory** is created. The program retains
  nothing between invocations.
- **No service, unit, daemon, or scheduled task** is registered. The program
  runs for approximately 800 microseconds when invoked and not otherwise.
- **No shell profile is modified.** Nothing is appended to your `~/.bashrc`.
- **No telemetry** is collected, transmitted, or enabled, and no network
  connection is made at install time or at run time.
- **No account is created**, locally or remotely.
- **No other package is installed** as a dependency, because there are none.
- **No post-install script runs.** `make install` copies files and exits.
- **Nothing is left behind on removal.** See
  [UNINSTALL.md](UNINSTALL.md), which is complete rather than approximate,
  precisely because of everything above.

---

**See also:** [UNINSTALL.md](UNINSTALL.md) ·
[README.md](README.md) ·
[INSTRUCTIONS.md](INSTRUCTIONS.md) ·
[CONTRIBUTING.md](CONTRIBUTING.md)
