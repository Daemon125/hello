# INSTRUCTIONS

**A complete guide to building and running `hello`, assuming no prior
knowledge, no software, and no computer.**

---

## Preface

This document explains how to run a program that prints `Hello, World!`.

It begins with the acquisition of a computer. This is not because acquiring a
computer is difficult, but because every other guide assumes you have one, and
a guide that assumes things is a guide that fails silently for the people it
assumed wrong about. The instructions here assume you are standing in a room
with nothing in it.

The program takes approximately 800 microseconds to run. Preparing to run it
takes between four minutes and eleven days depending on where you are starting
from. This document covers both cases and everything between them.

### How to use this document

Do not read it front to back. Use the decision below to find your entry point.

| Your situation | Start at |
|---|---|
| I have a computer with a compiler installed | [Part 9](#part-9-obtaining-the-source) |
| I have a computer and know what a terminal is | [Part 7](#part-7-installing-a-compiler) |
| I have a computer but have never opened a terminal | [Part 4](#part-4-the-terminal) |
| I have a computer and nothing else | [Part 3](#part-3-choosing-an-operating-system) |
| I do not have a computer | [Part 1](#part-1-choosing-a-computer) |
| I do not have a room to put a computer in | [Part 0](#part-0-before-you-begin) |

Most readers should start at Part 7 or Part 9. Parts 0 through 6 exist for
completeness and for the smaller number of readers who genuinely need them.

### Conventions

Text in a box like this is a command to type into a terminal, followed by the
Enter key:

```bash
echo hello
```

Do not type the `$` if you see one in other documentation; it represents the
prompt, not part of the command. This document omits it for that reason.

Text like `hello.c` refers to a filename. Text like <kbd>Ctrl</kbd>+<kbd>C</kbd>
means hold the first key and press the second.

Anything marked **STOP** is a point at which continuing without resolving the
issue will waste your time.

---

## Table of Contents

- [Part 0: Before You Begin](#part-0-before-you-begin)
- [Part 1: Choosing a Computer](#part-1-choosing-a-computer)
- [Part 2: Physical Setup](#part-2-physical-setup)
- [Part 3: Choosing an Operating System](#part-3-choosing-an-operating-system)
- [Part 4: The Terminal](#part-4-the-terminal)
- [Part 5: The Filesystem](#part-5-the-filesystem)
- [Part 6: Choosing a Text Editor](#part-6-choosing-a-text-editor)
- [Part 7: Installing a Compiler](#part-7-installing-a-compiler)
- [Part 8: Verifying the Compiler](#part-8-verifying-the-compiler)
- [Part 9: Obtaining the Source](#part-9-obtaining-the-source)
- [Part 10: Typing the Program](#part-10-typing-the-program)
- [Part 11: Saving the File](#part-11-saving-the-file)
- [Part 12: Compiling](#part-12-compiling)
- [Part 13: Running It](#part-13-running-it)
- [Part 14: Verifying the Output](#part-14-verifying-the-output)
- [Part 15: Troubleshooting](#part-15-troubleshooting)
- [Part 16: What You Have Actually Done](#part-16-what-you-have-actually-done)
- [Part 17: What To Do Next](#part-17-what-to-do-next)
- [Appendices](#appendices)

---

# Part 0: Before You Begin

## 0.1 Physical prerequisites

You will need:

- **A flat surface** at approximately elbow height when seated. A desk, a
  table, or a plank on two filing cabinets. See §1.11 for the correct height,
  which is more important than it sounds.
- **A seat.** See §1.10, which is the most important section in Part 1.
- **Mains electricity**, or a charged battery, or in the limiting case a
  sufficiently large solar panel. The program's own energy draw is negligible;
  the machine's is not.
- **Light** you can read by without leaning forward. Leaning forward is how
  posture problems begin.

## 0.2 Time

| Task | Realistic time |
|---|---|
| Reading this document in full | 90 minutes |
| Acquiring a computer, if you have none | 1–11 days |
| Installing an operating system | 30–90 minutes |
| Installing a compiler | 2–40 minutes |
| Typing the program | 30 seconds |
| Compiling it | Under 1 second |
| Running it | 0.0008 seconds |

The distribution is worth noting before you begin. Essentially all of the time
is preparation, and essentially none of it is the task. This proportion does
not change as you get better; it is the permanent shape of the work.

## 0.3 Expectations

When you finish, a machine will display thirteen characters and then stop
existing.

This is a smaller outcome than the effort suggests, and it is the correct
outcome. What you will have verified is that a chain of roughly fifteen
independent systems — editor, preprocessor, compiler, assembler, linker,
loader, kernel, driver, terminal, font engine, compositor, and the hardware
under all of it — is functioning end to end on your specific machine. The
greeting is a receipt for that. It is not the product.

## 0.4 What this document will not teach you

- The C programming language. See [Part 17](#part-17-what-to-do-next).
- How to use your operating system generally.
- Touch typing.
- Why any of this is the way it is. That is in the comments of
  [`hello.c`](hello.c), which run to 2,712 lines and are not required reading.

---

# Part 1: Choosing a Computer

## 1.1 First: do you need one?

**STOP.** Answer this before reading further.

Do you already have any of the following?

- A laptop or desktop computer of any age, running any operating system
- A Mac of any vintage
- A Chromebook
- A Raspberry Pi or similar single-board computer
- An Android phone
- An iPhone or iPad
- A games console with a Linux mode
- Access to a computer at a library, school, or workplace

If yes to **any** of these, you do not need to buy anything. Skip to
[Part 3](#part-3-choosing-an-operating-system). The requirements in §1.2 are
low enough that essentially every device manufactured in the last twenty years
will do this job, and several that were manufactured before that.

The remainder of Part 1 is for readers who genuinely have no access to a
computer, or who intend to buy one anyway and would like the decision made
carefully.

## 1.2 Requirements analysis

It is worth being precise about what this task actually demands, because the
answer is unlike what computer marketing will tell you.

**To compile and run this program you need:**

| Resource | Actually required | Typical new machine |
|---|---|---|
| CPU | Any 32-bit processor, ~100 MHz | 8+ cores at 3+ GHz |
| RAM | 16 MB | 8–32 GB |
| Storage | 50 MB (mostly the compiler) | 256 GB–2 TB |
| Display | 80×24 characters | 2 million+ pixels |
| Network | None | Required for setup |
| GPU | None | Present regardless |

A Pentium II from 1998 with 64 MB of RAM will compile this program in well
under a second. A Raspberry Pi Zero, which costs less than a sandwich in some
cities, exceeds the requirement by roughly two orders of magnitude.

**This is important and it generalizes.** The hardware requirement for learning
to program is essentially zero. It stays near zero for years. What eventually
raises it is not the code you write but the tools other people build to help
you write it — the browser-based editors, the language servers, the container
runtimes, the machine learning libraries. Buy for the tools you will eventually
run, not for the programs you will write, because your programs will be small
for a very long time.

## 1.3 Form factor

| Form factor | Advantages | Disadvantages | Verdict |
|---|---|---|---|
| **Desktop tower** | Cheapest per unit of performance; repairable; upgradeable; best thermals; you choose the keyboard and monitor separately | Immobile; requires separate monitor, keyboard, mouse; takes floor space | Best value if you will work in one place |
| **Laptop** | Portable; self-contained; no separate purchases; works during a power cut | 30–60% more expensive for equal performance; poor keyboard and screen relative to standalone equivalents; hard to repair; thermally limited | Best default for most people |
| **Mini PC / NUC** | Small; quiet; cheap; low power draw | Limited upgrade path; still needs peripherals | Good compromise |
| **Single-board computer** (Raspberry Pi) | $15–$80; low power; excellent for learning; genuinely disposable | Slow; needs peripherals, a power supply, and an SD card; assembly required | Best if budget is the binding constraint |
| **Tablet** | Portable; long battery | Software restrictions make local compilation difficult or impossible; on-screen keyboards are unsuitable for code | Not recommended |
| **Phone** | You already have one | Same as tablet, more so | See §1.3.1 |
| **Used enterprise laptop** | Extremely cheap; built to be repaired; excellent keyboards; parts available for a decade | Cosmetically worn; battery likely needs replacing | **See §1.14. This is the recommendation.** |

### 1.3.1 The phone case

It is possible to compile C on an Android phone (via Termux) or, with more
difficulty, on iOS (via a shell app or by connecting to a remote machine). If
this is genuinely your only device, it will work, and the exercise is
instructive.

It is not pleasant. Programming on a touchscreen is slow in a way that
compounds: every character costs more, so you write less, so you learn slower.
If there is any path to a physical keyboard, take it. A $20 Bluetooth keyboard
paired to a phone is a real improvement and a legitimate setup.

## 1.4 CPU architecture

| Architecture | Found in | Compiler support | Notes |
|---|---|---|---|
| **x86-64** (also called amd64) | Most desktops and laptops; Intel and AMD | Universal and mature | The default. Everything works. |
| **ARM64** (aarch64) | Apple Silicon Macs, most phones, Raspberry Pi 4/5, newer Windows laptops | Excellent | Efficient; occasionally an obscure tool has no build |
| **RISC-V** | Development boards; a small number of laptops | Good and improving fast | Choose this only if you specifically want to |
| **32-bit x86** | Machines from before ~2008 | Fine | Still supported; increasingly deprecated by distributions |

**For this task, all four are equivalent.** The program is architecture-neutral
and will compile on any of them without modification. That property is not an
accident; it is the reason C exists, and the history is in Volume II of
[`hello.c`](hello.c).

For general use, x86-64 has the widest software compatibility and ARM64 has
better battery life. Neither will limit you for years.

## 1.5 Memory (RAM)

| Amount | Suitable for |
|---|---|
| 2 GB | This program. A terminal and an editor. Nothing else. |
| 4 GB | A minimal Linux desktop, a text editor, and a browser with three tabs |
| **8 GB** | **A comfortable modern development setup. The realistic minimum for a new machine.** |
| 16 GB | Containers, virtual machines, a heavy IDE, a browser used normally |
| 32 GB+ | Large builds, multiple VMs, machine learning work |

**Buy 16 GB if you can afford it and 8 GB if you cannot.** RAM is the component
that most reliably determines whether a machine feels usable in five years, and
on most modern laptops it is soldered to the board and cannot be changed later.
Check before you buy: if the RAM is soldered, the amount you choose at purchase
is permanent.

## 1.6 Storage

**Get an SSD.** This is the single most consequential specification on the list
for how the machine feels to use. A mechanical hard disk is roughly a hundred
times slower for the small random reads that compilation, package installation,
and program launching consist almost entirely of. A ten-year-old machine with
an SSD feels faster than a new machine with a spinning disk, and this is not an
exaggeration.

If you are buying used and the machine has a mechanical disk, budget $25 for a
replacement SSD. It is the highest-return upgrade available and on most
machines it is four screws.

| Capacity | Adequate for |
|---|---|
| 128 GB | Linux, a compiler, and your code. Genuinely enough. |
| 256 GB | The above plus normal computer use |
| 512 GB+ | Comfortable; whatever you like |

Your source code will not fill any of these. `hello.c` is 136 kilobytes, and it
is 452 times larger than it needs to be. A career's worth of source code fits
in a few gigabytes.

## 1.7 Display

For reading and writing text, in order of importance:

1. **Resolution.** 1920×1080 is the practical minimum. Below that, you will see
   too few lines at once and will scroll instead of reading.
2. **Physical size and viewing distance.** A 24-inch monitor at arm's length is
   comfortable. A 13-inch laptop screen at the same distance is not, and you
   will lean in, and see §1.11.
3. **Matte versus glossy.** Matte, if you have the choice. Glossy screens
   reflect the room and you will position your whole body to avoid the
   reflection.
4. **Refresh rate.** Irrelevant for text. Ignore any marketing about it.
5. **Color accuracy.** Irrelevant unless you do design work.

A second monitor is the most commonly recommended productivity upgrade and it
is genuinely useful — documentation on one screen, code on the other. It is not
necessary and should not delay you.

## 1.8 The keyboard

You will interact with this machine almost entirely through the keyboard.
Treat it as the primary interface, because it is.

### 1.8.1 Layout

**Get a layout that matches the language you type in.** This sounds obvious and
is the most commonly regretted purchase decision, because keyboards bought
online frequently ship with a layout from another country.

For programming specifically, check the position of these keys before buying:

- <kbd>{</kbd> <kbd>}</kbd> <kbd>[</kbd> <kbd>]</kbd> — braces and brackets,
  used constantly in C
- <kbd>\\</kbd> — backslash, used in every escape sequence including the `\n`
  in this program
- <kbd>|</kbd> — pipe, the central operator of the Unix shell
- <kbd>~</kbd> — tilde, which means your home directory
- <kbd>Esc</kbd> — needed to leave `vim`, see §6.4

Some international layouts place these behind a modifier key combination,
which is workable but adds friction to characters you will type thousands of
times.

**ANSI vs ISO:** ANSI (common in the US) has a wide horizontal Enter key and a
long left Shift. ISO (common in Europe) has a tall Enter key and a shorter left
Shift with an extra key beside it. Neither is better. Use whichever you learned
on; switching between them is briefly maddening.

### 1.8.2 Switch type

| Type | Feel | Noise | Cost | Notes |
|---|---|---|---|---|
| **Membrane** | Soft, mushy | Quiet | $10–30 | Fine. Most laptops. Do not let anyone tell you this is unacceptable. |
| **Scissor** | Short, crisp | Quiet | Built in | Best laptop mechanism |
| **Mechanical, linear** | Smooth, no bump | Moderate | $50–150 | Popular for typing speed |
| **Mechanical, tactile** | Bump at actuation | Moderate | $50–150 | Best general recommendation |
| **Mechanical, clicky** | Bump plus loud click | **Loud** | $50–150 | Do not use in a shared room. This ends friendships. |
| **Topre / electrocapacitive** | Smooth with a dampened bump | Quiet | $200+ | Excellent, expensive, cult following |

A good keyboard is a genuine pleasure and a real long-term investment — they
last decades. It is also entirely optional. Every keyboard sold will type this
program correctly.

### 1.8.3 What to avoid

- Keyboards without a full-size Escape key
- Laptops that require a function-key combination for the arrow keys
- Anything where the Enter key is unusually small
- Wireless keyboards for a stationary machine (batteries, latency, pairing
  problems, all for no benefit at a desk)

## 1.9 Pointing device

Largely irrelevant for this task and for command-line work generally, which is
one of its attractions. Any mouse or trackpad will do.

If you use a mouse for many hours daily, a vertical mouse or a trackball
reduces forearm pronation and is worth trying if you have wrist discomfort.
This is a genuine ergonomic consideration and not an accessory upsell.

## 1.10 The chair

**This is the most important section in Part 1, and the one most likely to be
skipped.**

You will spend far more time in the chair than you will spend thinking about
the processor. Repetitive strain and back injury are the two occupational
hazards of this work; they arrive slowly, they arrive without warning, and they
are substantially harder to reverse than to prevent.

If your budget forces a choice between a better computer and a better chair,
**buy the chair.** The computer will be obsolete in six years. Your spine is
not on that replacement cycle.

### 1.10.1 What matters

1. **Seat height adjustment.** Non-negotiable. Feet flat on the floor, thighs
   roughly parallel to it, knees at approximately 90 degrees. If the chair
   cannot reach that position for your body, it is the wrong chair.
2. **Lumbar support.** The chair must support the inward curve of your lower
   back. A rolled towel against the back of a dining chair achieves this for
   free and works.
3. **Seat depth.** Two to four fingers of clearance between the seat edge and
   the back of your knees. Too deep and the edge compresses the back of your
   thigh.
4. **Armrests.** Adjustable, and set so your shoulders are relaxed and your
   forearms roughly parallel to the floor. Armrests that are too high raise
   your shoulders; too low and you will lean. If they cannot be adjusted and
   are wrong, remove them.
5. **A back that does not force you forward.** Many cheap chairs curve the
   wrong way.

### 1.10.2 Budget

| Budget | Option |
|---|---|
| $0 | A dining chair with a cushion and a rolled towel for lumbar support. Adjust the *desk* and *monitor* to fit the chair, since the chair cannot be adjusted. This works. |
| $100–200 | A basic adjustable office chair. Adequate. |
| $200–400 | A decent task chair with real adjustment range |
| $400–1500 | Herman Miller, Steelcase, Humanscale, and similar. Expensive, and they last twenty years, and the used market for them is excellent — see §1.14. |

**A used Steelcase Leap or Herman Miller Aeron in good condition costs $200–400
and is better than any new chair under $800.** Office liquidators sell them by
the pallet when companies downsize. This is the best value purchase in this
entire document.

### 1.10.3 The rule that matters more than the chair

No chair prevents injury from sitting still for six hours. Stand up every 30 to
45 minutes, even briefly. Set a timer if you will not remember, and you will
not remember.

## 1.11 The desk and monitor position

- **Desk height:** with your feet flat and your shoulders relaxed, your
  forearms should be roughly parallel to the floor when your hands are on the
  keyboard. Most fixed desks are 73–76 cm, which is too high for a large
  fraction of adults. If yours is too high, raise the chair and add a footrest;
  a stack of books works.
- **Monitor height:** the top of the screen at or slightly below eye level. You
  should look very slightly *down* at the center of the screen, not up.
- **Monitor distance:** an arm's length away, roughly 50–70 cm. Further is
  better than nearer.
- **Laptops violate both of the above by construction.** The screen and
  keyboard are attached, so you cannot have the screen at eye height and the
  keyboard at elbow height simultaneously. If you use a laptop as a primary
  machine for long sessions, raise it on a stand and add an external keyboard.
  A laptop stand and a $25 keyboard fix an ergonomic problem that is otherwise
  permanent.

## 1.12 Lighting

- Avoid a bright window directly behind the monitor; your eyes will constantly
  readjust between the bright background and the darker screen.
- Avoid a bright window directly behind *you*, which reflects off the screen.
- Windows to the side are ideal.
- Ambient room light should be roughly comparable to the screen brightness. A
  bright screen in a dark room is the most common cause of eye strain among
  people who work at night.

## 1.13 Budget tiers

| Tier | Cost | What to get | Suitable for |
|---|---|---|---|
| **Zero** | $0 | The device you already own; a library computer; a friend's machine | Everything in this document |
| **Minimal** | $15–80 | Raspberry Pi Zero 2 W or Pi 4, plus SD card, power supply, and cables. Use a TV as the monitor. | Learning to program, indefinitely |
| **Frugal** | $80–250 | Used business laptop: ThinkPad T480/T14, Dell Latitude 5000-series, HP EliteBook 840. Add an SSD if it lacks one. | Serious daily development work |
| **Standard** | $500–900 | New mid-range laptop, 16 GB RAM, 512 GB SSD | Everything most developers do |
| **Comfortable** | $1200–2000 | MacBook Air/Pro, ThinkPad X1/T-series, or a self-built desktop | Heavy builds, VMs, containers |
| **Excessive** | $3000+ | High-core-count workstation | Compiling large codebases; not this |

**For the great majority of readers who need to buy something, the Frugal tier
is the correct answer**, and it is not a compromise. A 2018 ThinkPad T480 with
16 GB of RAM and an SSD costs under $200, has a keyboard better than any
current laptop, has user-replaceable parts, has service manuals published by
the manufacturer, and will compile this program in the same time as a $4,000
workstation.

## 1.14 New, used, or refurbished

| Source | Price | Warranty | Recommendation |
|---|---|---|---|
| New retail | Highest | Full | If you want support and have the budget |
| Manufacturer refurbished | −15 to −30% | Usually full | Excellent value, low risk |
| Off-lease enterprise (business resellers) | −60 to −80% | 90 days typical | **Best value available** |
| Consumer used (marketplaces) | Lowest | None | Riskiest; inspect in person |

**Off-lease enterprise hardware is the best-kept secret in personal computing.**
Corporations lease machines on three-year cycles and dispose of them in bulk
regardless of condition. The machines were built to a higher standard than
consumer equivalents — magnesium frames, spill-resistant keyboards, published
service manuals, ten-year parts availability — and they arrive tested and
wiped, at a fifth of their original price.

### 1.14.1 What to check when buying used

- **Battery health.** Assume it needs replacing and budget $30–60. Any listed
  battery figure is optimistic.
- **Screen.** Ask for a photo of the display powered on showing a white image.
  Dead pixels and backlight bleed show up immediately.
- **Keyboard.** Ask for a photo of the keys. Shiny keycaps indicate very heavy
  use.
- **Hinges.** The most common mechanical failure on laptops and the most
  annoying to repair.
- **Storage type.** If mechanical, add $25 for an SSD (see §1.6).
- **RAM upgradeability.** Check whether it is socketed or soldered.
- **Firmware lock.** A BIOS or supervisor password left by the previous
  organization can render a machine unusable. Ask explicitly. This is the
  single most common problem with ex-corporate hardware.

## 1.15 What not to buy for this purpose

| Avoid | Reason |
|---|---|
| A gaming laptop | Pays for a GPU you will not use; loud; heavy; short battery life |
| A tablet with a keyboard cover | Software restrictions make local compilation difficult |
| The cheapest new laptop on the shelf | 4 GB of soldered RAM and mechanical storage; a used business machine at the same price is far better |
| Anything with under 8 GB of RAM, new | It cannot be fixed later if soldered |
| An extended warranty | Statistically poor value; the money is better spent on the chair |
| A machine chosen for its processor benchmark | See §1.2. The bottleneck in this work is never the CPU. |

## 1.16 The recommendation

If you have any computing device at all: **use it.** Go to
[Part 3](#part-3-choosing-an-operating-system).

If you must buy, in priority order:

1. **A used enterprise laptop** — ThinkPad T480 or T14, Dell Latitude
   5000-series, or HP EliteBook 840 — with 16 GB RAM and an SSD. $150–250.
2. **A used ergonomic chair** — Steelcase Leap or Herman Miller Aeron.
   $200–400. If forced to choose between items 1 and 2, buy this one first and
   use a library computer until you can afford the other.
3. **An external keyboard and a laptop stand.** $50 total. Fixes the ergonomic
   problem described in §1.11.
4. **A second-hand 24-inch 1080p monitor.** $50–80. Optional and pleasant.

Total: approximately $500 for a setup that will serve for a decade, of which
less than half is the computer.

---

# Part 2: Physical Setup

## 2.1 Unpacking

1. Open the box on the floor, not on the desk. Machines dropped during
   unpacking are almost always dropped from desk height.
2. Keep the box until the machine has run for a week. Returns require it.
3. Note the model and serial number somewhere that is not on the machine. You
   will need it for driver downloads, warranty claims, and theft reports.

## 2.2 Power

1. Connect the power supply before the first boot. A machine that arrives with
   a flat battery and is powered on immediately will shut down mid-setup, and
   an interrupted first boot occasionally requires starting over.
2. Use the supplied charger. Third-party chargers with incorrect voltage or
   insufficient wattage are a genuine fire risk and a common cause of
   intermittent, difficult-to-diagnose faults.
3. If you live somewhere with unstable mains power, a surge protector is worth
   the $20.

## 2.3 Position

Apply §1.10 through §1.12 now, before you start working, rather than after your
wrists begin to hurt. Specifically:

- Chair height set so your feet are flat and forearms are level
- Screen top at or just below eye level
- Screen at arm's length
- No window directly behind the screen or directly behind you

Setting this up takes four minutes once and saves an injury that takes months
to resolve.

## 2.4 First boot

The machine will present a setup wizard. It will ask for:

- A language and region
- A network connection
- An account name and password
- Consent to various data collection

On the last item: decline what you can. It is easier to decline now than to
find the settings later.

**Choose a password you can type quickly**, because you will type it many
times, and choose a different one from any password you use elsewhere. If the
machine offers full-disk encryption, accept it. The performance cost on modern
hardware is unmeasurable and the benefit if the machine is stolen is total.

---

# Part 3: Choosing an Operating System

## 3.1 The short answer

**Use the operating system already on the machine.** All three major ones can
compile C, and the differences do not matter for this task or for the next
several years of your work.

Reinstalling an operating system in order to run a six-line program is a
detour of several hours with no benefit. Read §3.2 for orientation and then
skip to [Part 4](#part-4-the-terminal).

## 3.2 The options

| OS | Compiler setup | Terminal quality | Notes |
|---|---|---|---|
| **Linux** | One command, pre-installed on many distributions | Excellent | The native environment for C. Everything in this document works without modification. |
| **macOS** | One command, prompts a download | Excellent | Unix underneath; nearly identical to Linux for this purpose |
| **Windows** | Several options, none of them one command | Historically poor, now good | See §3.4 |
| **BSD** | Pre-installed | Excellent | If you are running BSD you do not need this section |
| **ChromeOS** | Requires enabling Linux mode | Good once enabled | See §3.5 |

## 3.3 If you are installing Linux

Recommended distributions for someone doing this for the first time:

| Distribution | Why |
|---|---|
| **Linux Mint** | The gentlest transition from Windows. Everything works. Recommended for a first install. |
| **Ubuntu** | The most widely documented. Any error message you search will have an Ubuntu answer. |
| **Fedora** | Newer software; excellent hardware support; very well engineered |
| **Debian** | Extremely stable, somewhat older packages. What most servers run. |
| **Arch** | Do not start here. It is excellent and it will consume the week you meant to spend programming. |

Installation, in outline:

1. Download the ISO image from the distribution's official site
2. Write it to a USB stick (8 GB or larger) using Rufus on Windows, or
   `dd` on Unix, or the graphical tool your distribution supplies
3. **Back up everything on the machine first.** Installation will offer to
   erase the disk and, at some point, someone always accepts that offer
   accidentally.
4. Boot from the USB stick — usually <kbd>F12</kbd>, <kbd>F2</kbd>, or
   <kbd>Del</kbd> during startup, which varies by manufacturer
5. Try the live session before installing. If the wireless, sound, and display
   work in the live session, they will work after installation.
6. Install

## 3.4 If you are on Windows

Four routes, in order of recommendation:

### 3.4.1 WSL (Windows Subsystem for Linux) — recommended

Gives you a genuine Linux environment inside Windows. Everything in this
document then applies unmodified.

```powershell
wsl --install
```

Run that in PowerShell as Administrator, restart, and you have Ubuntu. This is
the best option for anyone learning Unix-style development on Windows and it
is now a supported, first-class feature rather than a workaround.

### 3.4.2 MSYS2 / MinGW-w64

A Unix-like toolchain producing native Windows executables. Good if you
specifically want `.exe` files that run without WSL.

### 3.4.3 Visual Studio / MSVC

Microsoft's own compiler. Excellent, and a very large download (several
gigabytes). The command-line invocation differs from everything in this
document: `cl hello.c` rather than `cc -o hello hello.c`.

### 3.4.4 Cygwin

Older, still maintained, largely superseded by WSL. Use it only if you have a
specific reason.

## 3.5 If you are on ChromeOS

Enable Linux from Settings → Advanced → Developers → Linux development
environment. This provisions a Debian container. Everything in this document
then works.

## 3.6 If you are on a Raspberry Pi

Raspberry Pi OS ships with GCC pre-installed. You are already finished with
Parts 3 and 7. Skip to [Part 4](#part-4-the-terminal).

---

# Part 4: The Terminal

## 4.1 What it is

A terminal is a program that displays text and accepts typed commands. Inside
it runs a *shell* — a program that reads what you type, finds the corresponding
program, runs it, and shows you the output.

The distinction matters occasionally: the terminal is the window, the shell is
the thing interpreting your words. Common shells are `bash`, `zsh` (the default
on macOS), and `fish`.

## 4.2 Why it looks like that

The terminal is an emulation of a physical device. Terminals were real
machines — a keyboard and a screen connected to a distant computer by a serial
cable — and the DEC VT100 of 1978 was common enough that its control sequences
became a de facto standard. Your terminal emulator still implements them.

This is why the interface is a grid of fixed-width characters, why colors are
set with escape sequences that begin with an invisible control character, and
why the window has 80 columns by default: the IBM punched card, standardized in
1928, held 80 characters per row.

## 4.3 Why use it at all

For this task, because compilers are command-line programs. More generally,
because the interface is composable in a way graphical interfaces are not: the
output of any program can become the input of any other, which means tools do
not need to anticipate their uses.

You do not have to like it. You do have to be able to use it.

## 4.4 Opening one

| System | How |
|---|---|
| **macOS** | <kbd>Cmd</kbd>+<kbd>Space</kbd>, type `Terminal`, press Enter |
| **Ubuntu / Mint / most Linux** | <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>T</kbd> |
| **Any Linux desktop** | Search the applications menu for "Terminal" |
| **Windows (WSL)** | Open "Windows Terminal" or "Ubuntu" from the Start menu |
| **Windows (native)** | Start menu → "PowerShell" or "Command Prompt" |
| **ChromeOS** | Applications → Linux apps → Terminal |
| **Raspberry Pi** | The terminal icon in the taskbar |

## 4.5 What you will see

Something resembling:

```
username@hostname:~$
```

This is the **prompt**. Reading it left to right: your username, the machine's
name, the directory you are currently in (`~` means your home directory), and a
symbol indicating the shell is ready. On macOS the format differs slightly; on
Windows it differs more.

The prompt is not part of any command. When documentation shows `$ ls`, type
only `ls`.

## 4.6 The six commands you need

Type each of these and press Enter.

### `pwd` — print working directory

```bash
pwd
```

Prints where you currently are. The shell always has a current directory, and
every relative filename is interpreted from it. When something cannot be found,
this is the first command to run.

### `ls` — list

```bash
ls
```

Lists the files in the current directory. Useful variants:

```bash
ls -l     # long format: permissions, size, date
ls -a     # include hidden files (those beginning with a dot)
ls -la    # both
```

### `cd` — change directory

```bash
cd Documents      # move into Documents
cd ..             # move up one level
cd ~              # go to your home directory
cd                # also goes to your home directory
cd -              # go back to the previous directory
```

### `mkdir` — make directory

```bash
mkdir hello
```

### `cat` — print a file

```bash
cat hello.c
```

Prints a file's contents. Named for *concatenate*, because given several files
it prints them in sequence — which is its actual purpose and almost never how
anyone uses it.

### `clear` — clear the screen

```bash
clear
```

Or press <kbd>Ctrl</kbd>+<kbd>L</kbd>.

## 4.7 Essential keys

| Key | Effect |
|---|---|
| <kbd>Tab</kbd> | **Autocomplete.** Type a few letters of a filename and press it. Use this constantly; it prevents typos and confirms the file exists. |
| <kbd>↑</kbd> / <kbd>↓</kbd> | Previous and next command in history |
| <kbd>Ctrl</kbd>+<kbd>C</kbd> | Cancel the running program. The universal escape hatch. |
| <kbd>Ctrl</kbd>+<kbd>D</kbd> | End of input; also exits the shell |
| <kbd>Ctrl</kbd>+<kbd>L</kbd> | Clear the screen |
| <kbd>Ctrl</kbd>+<kbd>A</kbd> / <kbd>Ctrl</kbd>+<kbd>E</kbd> | Jump to start / end of the line |
| <kbd>Ctrl</kbd>+<kbd>U</kbd> | Delete the line |
| <kbd>Ctrl</kbd>+<kbd>R</kbd> | Search command history |

**<kbd>Tab</kbd> is the most important key in this table.** Typing full
filenames by hand is a source of errors that <kbd>Tab</kbd> eliminates
entirely.

## 4.8 A warning

Two commands can destroy your data instantly and without confirmation:

```bash
rm -rf <path>       # deletes a directory and everything in it, permanently
dd if=... of=...    # writes raw data to a device, including your disk
```

There is no recycle bin. There is no undo. Never paste a command containing
either of these from a source you do not trust, and read them twice before
running them.

---

# Part 5: The Filesystem

## 5.1 The shape of it

Files live in a tree. On Unix the root is `/`; on Windows each drive has its
own root such as `C:\`.

```
/
├── home/
│   └── yourname/          <-- your home directory, abbreviated ~
│       ├── Documents/
│       ├── Downloads/
│       └── code/          <-- create this
├── usr/
│   ├── bin/               <-- where installed programs live
│   └── include/           <-- where stdio.h lives
├── etc/                   <-- system configuration
└── tmp/                   <-- temporary files, cleared on reboot
```

On macOS your home directory is `/Users/yourname`. On Linux it is
`/home/yourname`. Both are `~`.

## 5.2 Absolute and relative paths

- **Absolute** paths start at the root: `/home/yourname/code/hello.c`. They
  mean the same thing from anywhere.
- **Relative** paths start from the current directory: `hello.c`, or
  `code/hello.c`, or `../hello.c`.

`.` means the current directory and `..` means the one above it. The `.` in
`./hello` in [Part 13](#part-13-running-it) is this, and §13.2 explains why it
is required.

## 5.3 Making a place to work

```bash
cd ~
mkdir -p code/hello
cd code/hello
pwd
```

The last command should print something ending in `/code/hello`. You are now in
a directory that exists for this purpose and nothing else.

`-p` means create parent directories as needed and do not complain if they
already exist.

## 5.4 A note on filenames

- **Avoid spaces.** `hello world.c` requires quoting in every command that
  touches it. Use `hello_world.c` or `hello-world.c`.
- **The extension matters to the compiler.** A file ending in `.c` is compiled
  as C; a file ending in `.cpp` is compiled as C++; a file with no extension
  will be rejected.
- **Case matters** on Linux. `Hello.c` and `hello.c` are different files. On
  macOS and Windows it usually does not, which causes problems the first time
  you move code to a Linux machine.
- **Windows hides extensions by default.** This causes a specific and common
  failure: you save `hello.c` in Notepad and Windows silently creates
  `hello.c.txt`. Enable "File name extensions" in Explorer's View tab before
  you begin.

---

# Part 6: Choosing a Text Editor

## 6.1 What an editor is not

A text editor writes plain text — bytes, exactly as typed, with nothing added.

A **word processor** (Microsoft Word, Google Docs, Apple Pages) does not do
this. It stores formatting, and it silently rewrites what you type: straight
quotes become curly quotes, hyphens become dashes, the first letter of a line
becomes capitalized.

**A C compiler cannot read a word processor file, and curly quotes are not
valid C.** This is the single most common failure mode for a first program, and
the resulting error message does not mention quotation marks. Do not use a word
processor.

## 6.2 The options

| Editor | Difficulty | Where | Recommendation |
|---|---|---|---|
| **nano** | Trivial | Pre-installed on nearly every Unix system | **Start here.** Commands are listed at the bottom of the screen. |
| **VS Code** | Easy | Free download | The most widely used editor. Excellent. Large. |
| **Notepad++** | Easy | Windows, free | Good lightweight Windows choice |
| **gedit / Kate / TextEdit** | Easy | Pre-installed | Fine. Set TextEdit to plain text mode first — see §6.5. |
| **Sublime Text** | Easy | Paid, unlimited trial | Very fast |
| **vim** | Steep | Pre-installed nearly everywhere | Worth learning eventually. See §6.4 first. |
| **emacs** | Steep | Free | Worth learning eventually. Different philosophy. |
| **Notepad** | Trivial | Windows | Works, but see §5.4 regarding extensions |

## 6.3 Using nano

```bash
nano hello.c
```

Type. The commands are shown at the bottom of the screen, where `^` means
<kbd>Ctrl</kbd>:

| Keys | Action |
|---|---|
| <kbd>Ctrl</kbd>+<kbd>O</kbd> | Write out (save) — then press Enter to confirm the name |
| <kbd>Ctrl</kbd>+<kbd>X</kbd> | Exit |
| <kbd>Ctrl</kbd>+<kbd>K</kbd> | Cut the current line |
| <kbd>Ctrl</kbd>+<kbd>W</kbd> | Search |

nano is not a lesser editor. It is a complete one that does not require
learning anything before you can use it, and using it for years is a legitimate
choice.

## 6.4 Exiting vim

If you have opened `vim` accidentally — which happens, because it is the
default editor for several tools — you cannot exit by typing "quit", "exit", or
<kbd>Ctrl</kbd>+<kbd>C</kbd>. This is the most-searched programming question in
the world and there is no shame in it.

**To exit without saving:**

1. Press <kbd>Esc</kbd>
2. Type `:q!`
3. Press <kbd>Enter</kbd>

**To save and exit:**

1. Press <kbd>Esc</kbd>
2. Type `:wq`
3. Press <kbd>Enter</kbd>

The reason is that vim is *modal*: it starts in a mode where keys are commands
rather than text. <kbd>Esc</kbd> returns to that mode from anywhere, `:`
begins a command, `w` writes, `q` quits, and `!` forces. It is an entirely
coherent design and it is genuinely fast once learned. It is also the reason a
generation of programmers has restarted a terminal in frustration.

## 6.5 A warning about TextEdit (macOS)

TextEdit defaults to rich text and will save a `.rtf` file that the compiler
cannot read. Before using it:

**Format → Make Plain Text** (<kbd>Shift</kbd>+<kbd>Cmd</kbd>+<kbd>T</kbd>)

Then, in Preferences, disable "Smart quotes" and "Smart dashes", which will
otherwise convert your `"` characters into typographic quotes that are not
valid C.

## 6.6 Which to choose

- Never used a terminal editor: **nano**
- Want a modern graphical editor to grow into: **VS Code**
- On Windows and want something small: **Notepad++**
- Want to invest in a tool you will use for thirty years: **vim** or **emacs**,
  but not today

---

# Part 7: Installing a Compiler

## 7.1 What a compiler is

A compiler translates source code — the text you write — into machine
instructions the processor can execute. `cc`, `gcc`, and `clang` are compilers.
`cc` is a conventional name that points at whichever one your system provides.

You need exactly one. You very likely already have one.

## 7.2 Check first

```bash
cc --version
```

If that prints version information, **you already have a compiler.** Skip to
[Part 8](#part-8-verifying-the-compiler).

If it prints `command not found`, continue.

## 7.3 Linux — Debian, Ubuntu, Mint, Pop!_OS

```bash
sudo apt update
sudo apt install build-essential
```

`sudo` runs the command as the administrator and will ask for your password.
Nothing appears as you type it — no dots, no asterisks. This is deliberate and
the password is being received. `build-essential` is a bundle containing GCC,
the standard library headers, `make`, and the other tools normally needed.

## 7.4 Linux — Fedora, RHEL, CentOS, Rocky

```bash
sudo dnf install gcc
```

Or, for the full set:

```bash
sudo dnf groupinstall "Development Tools"
```

## 7.5 Linux — Arch, Manjaro

```bash
sudo pacman -S base-devel
```

## 7.6 Linux — openSUSE

```bash
sudo zypper install gcc
```

## 7.7 Linux — Alpine

```bash
apk add build-base
```

## 7.8 macOS

```bash
xcode-select --install
```

A dialog will appear offering to install the Command Line Developer Tools.
Accept it. The download is roughly 1–2 GB and takes several minutes.

This installs Clang, which on macOS answers to the names `cc` and `gcc` as
well. You do not need the full Xcode application, which is far larger, unless
you intend to write iOS or Mac applications.

## 7.9 Windows — WSL

Inside your WSL terminal, use §7.3. The Ubuntu instructions apply exactly.

## 7.10 Windows — MSYS2

1. Download and run the installer from the MSYS2 project site
2. Open the "MSYS2 UCRT64" terminal from the Start menu
3. Run:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

## 7.11 Windows — Visual Studio

1. Download the Visual Studio Installer from Microsoft
2. Select the "Desktop development with C++" workload
3. Install — this is several gigabytes
4. Use the "Developer Command Prompt" from the Start menu, not the ordinary
   Command Prompt, because the compiler is not on the default `PATH`

The compile command differs from the rest of this document:

```
cl hello.c
```

## 7.12 FreeBSD, OpenBSD, NetBSD

Clang or GCC is part of the base system. You have one already.

## 7.13 If you cannot install anything

If you are on a machine where you lack permission to install software — a
school or work computer — the following work without installation:

- **An online compiler** in a browser: godbolt.org, replit.com, or
  onlinegdb.com. All will compile and run this program.
- **A remote machine** you can reach over SSH.
- **A live USB.** Boot a Linux distribution from a USB stick without installing
  it. The compiler is available in the live session.

The online route is legitimate and skips Parts 2 through 8 entirely.

---

# Part 8: Verifying the Compiler

Before writing anything, confirm the compiler works. This separates *compiler
not installed correctly* from *program typed incorrectly*, which are otherwise
easy to confuse.

## 8.1 Check the version

```bash
cc --version
```

Expected output, in some form:

```
gcc (Ubuntu 13.2.0-4ubuntu3) 13.2.0
```

or

```
Apple clang version 15.0.0 (clang-1500.1.0.2.5)
```

The exact version does not matter. Any release from the last twenty years will
compile this program.

## 8.2 Check the headers

```bash
echo '#include <stdio.h>' | cc -E -xc - > /dev/null && echo "headers OK"
```

This asks the compiler to preprocess a one-line program that includes the
standard I/O header, discards the output, and reports success. If it prints
`headers OK`, the standard library headers are installed and findable.

If it reports that `stdio.h` cannot be found, you have a compiler but not the
standard library development files. On Debian-family systems, install
`libc6-dev` — though `build-essential` from §7.3 includes it.

## 8.3 Check the linker

```bash
printf 'int main(void){return 0;}' > /tmp/t.c && cc -o /tmp/t /tmp/t.c && /tmp/t && echo "linker OK"
```

This writes a minimal program that does nothing, compiles it, links it, runs
it, and confirms it exited successfully. If it prints `linker OK`, the entire
toolchain is functional and the rest of this document is a formality.

**STOP.** If §8.1 through §8.3 do not all succeed, resolve that before
continuing. Every error in Part 15 assumes a working toolchain, and diagnosing
a broken toolchain through a program's error messages is considerably harder
than diagnosing it directly.

---

# Part 9: Obtaining the Source

Two options. Both produce the same result.

## 9.1 Option A: use the file in this repository

If you have `hello.c`, use it:

```bash
cd ~/code/hello        # or wherever the file is
ls hello.c
```

If `ls` prints `hello.c`, skip to [Part 12](#part-12-compiling).

Note that this file is 136 kilobytes and 2,718 lines,
of which 6 are the program. The remainder is commentary and has no effect
on the compiled output.
You are not expected to read it.

## 9.2 Option B: type it yourself

**This is the better option if you are learning.** Copying a file teaches you
nothing; typing six lines and getting one of them wrong teaches you how to
read a compiler error, which is the actual skill.

Continue to [Part 10](#part-10-typing-the-program).

---

# Part 10: Typing the Program

Open your editor:

```bash
nano hello.c
```

Type the following exactly. Each line is explained afterward.

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");

    return 0;
}
```

## 10.1 Line by line

### Line 1: `#include <stdio.h>`

| Element | Meaning |
|---|---|
| `#` | Marks a **preprocessor directive**. It must be the first non-whitespace character on the line. The preprocessor is a separate, purely textual pass that runs before the compiler proper. |
| `include` | The directive: insert the contents of another file here. |
| `<stdio.h>` | The file to insert. **Angle brackets** mean search the system's include directories. **Double quotes** (`"myfile.h"`) would mean search the current directory first. |
| *(no semicolon)* | Preprocessor directives are not statements and do not take one. Adding a semicolon here is a common early error. |

`stdio.h` — *standard input/output header* — does not contain `printf`. It
contains a **declaration** of `printf`: a statement that a function of that name
exists, takes a format string followed by any number of further arguments, and
returns an `int`. The actual code lives in the C library and is attached at link
time.

This line is not optional. `printf` takes a variable number of arguments, and
the calling convention for such functions differs from ordinary ones on many
platforms. Without the declaration, the compiler cannot know how to arrange the
call, and the standard defines the result as undefined behavior.

### Line 2: blank

Ignored entirely. C does not care about whitespace between tokens. This line
exists for the reader.

### Line 3: `int main(void)`

| Element | Meaning |
|---|---|
| `int` | The **return type**. `main` returns an integer to the operating system. This word was optional before 1999 and is now required. |
| `main` | The name. This specific name is where execution begins in every hosted C program; the runtime calls it. Naming it anything else produces a program that compiles and fails to link. |
| `(void)` | The **parameter list**. `void` here means *takes no arguments*. |

**On `(void)` versus `()`:** empty parentheses in C mean *the parameters are
unspecified*, not *there are none* — a piece of K&R-era compatibility that
disables argument checking. Always write `(void)` when a function takes no
arguments. This distinction does not exist in C++, where both forms mean the
same thing.

**Do not write `void main()`.** It is not valid C. The standard specifies
`int main(void)` or `int main(int argc, char **argv)`. Compilers that accept
`void main()` are extending the language, not following it.

### Line 4: `{`

The **opening brace**. Begins a block — a region of code with its own scope.
Everything until the matching `}` is the body of `main`.

Braces are inherited from ALGOL 60, which spelled them `begin` and `end`; BCPL
shortened them, and every language descended from C copied the shortening.

Placing the brace on its own line versus at the end of the previous line is the
oldest unresolved argument in the field. Both are correct. This document uses
the K&R style for functions.

### Line 5: `    printf("Hello, World!\n");`

The only line that does anything.

| Element | Meaning |
|---|---|
| `    ` | Four spaces of **indentation**. Ignored by the compiler. Present for the human reader. Use spaces or tabs consistently; do not mix them in one file. |
| `printf` | The function being called. Named for *print formatted*. |
| `(` | Begins the argument list |
| `"` | Begins a **string literal**. Must be a straight double quote (U+0022). A typographic quote — `"` or `"` — is not valid C, and word processors insert them automatically. See §6.5. |
| `Hello, World!` | Thirteen characters, stored as bytes. |
| `\n` | An **escape sequence**: backslash followed by `n`, two characters in the source, which the compiler converts into the single newline character (byte value 10). This is not decorative — see §10.2. |
| `"` | Ends the string literal |
| `)` | Ends the argument list |
| `;` | The **statement terminator**. Required. Its absence is the most common compile error in the language, and the error is usually reported on the *following* line, because that is where the compiler first notices something is wrong. |

### Line 6: blank

Ignored.

### Line 7: `    return 0;`

Returns the value `0` from `main` to whatever started the program.

By convention, `0` means success and any other value means failure. This
convention is not enforced by the language; it is a Unix agreement that the
rest of the world adopted.

Since C99 this line is optional in `main` specifically — falling off the end
returns 0 automatically. It is written out here because relying on that rule
requires the reader to know it, and most readers do not.

`0` here does not mean the greeting was good, or useful, or received. It means
nothing went wrong.

### Line 8: `}`

The **closing brace**, matching line 4. Ends the body of `main`.

Every `{` must have exactly one matching `}`. Editors will highlight the match
when the cursor is on one; use it.

## 10.2 On the `\n`

The two characters `\` and `n` in the source become one byte in the compiled
program: the newline, ASCII 10.

It is doing real work. When output goes to a terminal, the C library uses
**line buffering** — it accumulates characters and sends them onward only when
it sees a newline. Remove the `\n` and the text sits in a buffer until the
program exits.

For a program this short, the output would appear either way, roughly a
microsecond apart. The lesson matters later: a long-running program that
crashes loses whatever is still in its buffer, which is why the last line
printed before a crash is so often not the last line that executed.

The newline also returns the cursor to the start of a fresh line, so the shell
prompt appears where it should rather than jammed against the `!`.

## 10.3 Characters that must be exact

| Character | Correct | Frequently wrong |
|---|---|---|
| Double quote | `"` (U+0022) | `"` `"` from word processors |
| Single quote | `'` (U+0027) | `'` `'` |
| Semicolon | `;` | `:` (colon) |
| Braces | `{` `}` | `(` `)` or `[` `]` |
| Backslash | `\` | `/` (forward slash) |
| Angle brackets | `<` `>` | Unicode look-alikes |

The backslash and forward slash confusion is worth special attention:
`"Hello, World!/n"` compiles without error and prints `Hello, World!/n`
literally, with no newline. It is a valid program that is silently wrong, which
is worse than one that fails to build.

## 10.4 Case sensitivity

C is case-sensitive throughout. `printf`, `Printf`, and `PRINTF` are three
different names, of which only the first exists. `int` is a keyword; `Int` is
not. `main` must be lowercase.

---

# Part 11: Saving the File

## 11.1 In nano

1. <kbd>Ctrl</kbd>+<kbd>O</kbd> — write out
2. Confirm the filename `hello.c` and press <kbd>Enter</kbd>
3. <kbd>Ctrl</kbd>+<kbd>X</kbd> — exit

## 11.2 In a graphical editor

**File → Save As**, and then:

- Set the filename to exactly `hello.c`
- Set the file type to "All Files" or "Plain Text" — **not** "Text Document
  (\*.txt)", which will append `.txt`
- Save it in the directory you created in §5.3

## 11.3 Verify it saved correctly

```bash
ls -l hello.c
```

Expected: a line showing the file and a size of roughly 80–100 bytes.

**If `ls` reports "No such file or directory":** the file was saved somewhere
else. Run `pwd` to see where you are, and search for it:

```bash
find ~ -name "hello.c*" 2>/dev/null
```

Note the `*` in that pattern: it will also find `hello.c.txt`, which is the
most likely problem. See §5.4.

## 11.4 Verify the contents

```bash
cat hello.c
```

The file should print back exactly what you typed. Check specifically:

- The quotes are straight, not curly
- Every line that should end in `;` does
- The braces match

---

# Part 12: Compiling

## 12.1 The command

```bash
cc -o hello hello.c
```

## 12.2 What each part means

| Part | Meaning |
|---|---|
| `cc` | The compiler. A conventional name pointing at whichever compiler your system provides. `gcc` or `clang` work identically here. |
| `-o hello` | **Output** to a file named `hello`. Without this, the output is named `a.out` — a name that dates to the first Unix assembler in 1971 and means *assembler output*. |
| `hello.c` | The input file. |

Note the order: the flag and its value come before the source file by
convention, though the compiler accepts them in any order.

## 12.3 Recommended: enable warnings

```bash
cc -Wall -Wextra -o hello hello.c
```

| Flag | Meaning |
|---|---|
| `-Wall` | Enable common warnings. Despite the name, this is not all warnings. |
| `-Wextra` | Enable more warnings. Together with `-Wall`, still not all of them. |
| `-pedantic` | Warn about anything not strictly conforming to the standard |
| `-std=c99` | Compile against a specific standard version |
| `-O2` | Optimize. Irrelevant for this program; standard for real ones. |
| `-g` | Include debugging information, so a debugger can show you source lines |

**Turn warnings on and keep them on.** A compiler warning is the cheapest bug
report you will ever receive: it arrives before the program has run, it names
the file and line, and it is usually right. Working with warnings disabled is
the most common self-inflicted wound in C.

The full recommended invocation:

```bash
cc -Wall -Wextra -pedantic -std=c99 -O2 -o hello hello.c
```

This program produces no diagnostics under it.

## 12.4 What success looks like

**Nothing.**

The compiler prints no output on success. This is the Unix convention: silence
means it worked. A tool that announces its own success is generating noise that
must be filtered by anything reading its output.

If you saw nothing, it worked.

## 12.5 Verify the executable exists

```bash
ls -l hello
```

Expected: a file of roughly 16–35 KB with an `x` in the permission string on
the left, indicating it is executable.

```
-rwxr-xr-x  1 you  staff  33432 Aug 22 14:31 hello
```

The `x` characters are the important part. If they are absent, the file is not
executable, and §15.9 covers that.

## 12.6 What just happened

The command ran four programs in sequence, silently:

1. **The preprocessor** handled `#include`, inserted roughly 1,500 lines from
   `stdio.h`, and stripped every comment
2. **The compiler** parsed the result and generated assembly for your specific
   processor
3. **The assembler** encoded that assembly into machine instructions
4. **The linker** combined it with the C runtime startup code and the parts of
   `libc` containing `printf`, and produced an executable file

You can see the intermediate stages:

```bash
cc -E hello.c | wc -l        # preprocessor output, in lines
cc -S hello.c && cat hello.s # the assembly the compiler generated
```

The second is worth running once. The assembly for this program is short enough
to read in full, and seeing it demystifies what a compiler is more effectively
than any explanation.

---

# Part 13: Running It

## 13.1 The command

```bash
./hello
```

## 13.2 Why `./` is required

The shell finds programs by searching a list of directories held in the `PATH`
environment variable. See it:

```bash
echo $PATH
```

The current directory is **not** on that list, deliberately. If it were, an
attacker who could write a file into a directory you visit could name it `ls`,
and you would run it the next time you typed `ls`.

`./hello` is an explicit path — `.` means *the current directory* — and
bypasses the search. This is why every Unix tutorial has that `./` and why it
is not a typo.

## 13.3 Expected output

```
Hello, World!
```

Followed by your shell prompt on the next line.

## 13.4 Check the exit status

```bash
./hello
echo $?
```

`$?` holds the exit status of the last command. It should print `0`.

This is how one program tells another whether it succeeded. It is the entire
mechanism, and it is one byte wide.

---

# Part 14: Verifying the Output

For confidence beyond looking at it.

## 14.1 Exact string comparison

```bash
test "$(./hello)" = "Hello, World!" && echo PASS || echo FAIL
```

## 14.2 Byte count

```bash
./hello | wc -c
```

Expected: `14`. Thirteen visible characters plus the newline.

If this prints `13`, your `\n` is missing or was typed as `/n`.

## 14.3 Byte-level inspection

```bash
./hello | od -c
```

Expected:

```
0000000    H   e   l   l   o   ,       W   o   r   l   d   !  \n
0000016
```

This shows every byte the program emitted, with the newline visible as `\n`.
`od` is *octal dump*, and `-c` asks for characters. It is the correct tool
whenever you need to know what a file or stream actually contains rather than
what it appears to contain — trailing whitespace, missing newlines, and
Windows-style line endings are all invisible until you look at it this way.

## 14.4 Confirm it works when redirected

```bash
./hello > out.txt
cat out.txt
rm out.txt
```

The program behaves identically. It does not know where its output goes, and
that is by design — see Volume II, §11.2 of [`hello.c`](hello.c).

---

# Part 15: Troubleshooting

## 15.1 `cc: command not found`

No compiler installed. Return to [Part 7](#part-7-installing-a-compiler).

## 15.2 `hello.c: No such file or directory`

The compiler cannot find your source file.

```bash
pwd            # where am I?
ls             # what is here?
find ~ -name "hello.c*" 2>/dev/null
```

Most likely: you are in a different directory than the file, or the file was
saved as `hello.c.txt`. See §5.4.

## 15.3 `stdio.h: No such file or directory`

The compiler is installed but the standard library headers are not. On
Debian-family systems:

```bash
sudo apt install libc6-dev
```

On macOS, re-run `xcode-select --install`.

## 15.4 `expected ';' before ...` / `expected declaration or statement at end of input`

A missing semicolon or a missing closing brace.

**The reported line number is usually one line *after* the actual mistake.**
The compiler continues reading until the construct becomes impossible, which is
typically on the next line. When an error points at a line that looks correct,
examine the line above it.

## 15.5 `warning: implicit declaration of function 'printf'`

Missing `#include <stdio.h>`, or it is misspelled. Check for `stdio.h` versus
`studio.h`, which is the classic version of this error.

## 15.6 `undefined reference to 'printf'` / `Undefined symbols`

This is a **linker** error rather than a compiler error — the code compiled and
the linker could not find the function.

Usually caused by compiling with `-c` (which stops before linking), or by a
misspelled function name that happens to be a valid identifier.

## 15.7 `stray '\342' in program` or similar

Non-ASCII characters in the source. Almost always typographic quotes inserted
by a word processor. Retype the quotes in a plain text editor. See §6.1.

Find them:

```bash
grep -n '[^\x00-\x7F]' hello.c
```

## 15.8 `hello: command not found`

You typed `hello` instead of `./hello`. See §13.2.

## 15.9 `permission denied`

The file is not marked executable:

```bash
chmod +x hello
```

If this happens after a normal compile, the filesystem may be mounted with
`noexec` — common for USB drives and some network shares. Copy the file to your
home directory and run it from there.

## 15.10 The program prints `Hello, World!/n`

You typed a forward slash instead of a backslash. This compiles cleanly and is
silently wrong, which makes it more instructive than an error.

## 15.11 Nothing prints, but there is no error

- Confirm the executable was rebuilt after your last edit — `cc` does not
  detect changes, it just does what you tell it
- Confirm you are running the file you just built:

```bash
ls -l hello.c hello    # is hello newer than hello.c?
```

## 15.12 `bash: ./hello: cannot execute binary file`

Architecture mismatch — you are trying to run a binary built for a different
processor. This happens when copying an executable between machines. Recompile
on the machine where you intend to run it.

## 15.13 Windows: `'cc' is not recognized`

You are in the ordinary Command Prompt rather than a developer environment.
Use the Developer Command Prompt (§7.11), or WSL (§7.9), or the MSYS2 terminal
(§7.10).

## 15.14 It worked yesterday and does not today

```bash
which cc              # is it still there?
cc --version          # does it still run?
pwd                   # are you where you think you are?
```

An operating system update that replaced the developer tools is the usual
cause on macOS. Re-run `xcode-select --install`.

## 15.15 General method

When something fails, in this order:

1. **Read the error message.** All of it, including the line number. Compiler
   errors are terse but they are precise and they are usually correct.
2. **Look one line above the reported line.** See §15.4.
3. **Verify your assumptions with commands, not memory.** `pwd`, `ls`,
   `cat hello.c`, `cc --version`. Nearly every stuck beginner is stuck because
   something they believe is true is not.
4. **Change one thing at a time.** Changing three things and retesting tells
   you nothing about which one mattered.
5. **Search the exact error text**, in quotes, minus your specific filenames.
   Someone has had this error. Probably in 2009.

---

# Part 16: What You Have Actually Done

You have not, primarily, printed a greeting.

You have verified that the following are present, correctly configured, and
functioning together on this specific machine:

| Layer | Verified by |
|---|---|
| A text editor writing plain bytes | The file compiled |
| The C preprocessor | `#include` resolved |
| The standard library headers | `stdio.h` was found |
| The compiler front end | The source parsed |
| The compiler back end | Machine code was generated for your processor |
| The assembler | Instructions were encoded |
| The linker | `printf` was resolved against `libc` |
| The C runtime | `main` was called |
| The loader | The image was mapped into memory |
| The kernel | The process was scheduled; `write` succeeded |
| The terminal driver and emulator | Bytes became glyphs |
| The font rasterizer and compositor | Glyphs became pixels |
| The display hardware | Pixels became photons |

Any one of these failing produces nothing at all. The output is binary in the
strict sense: either the entire stack is standing, or the screen is blank.

This is why the first program is a greeting rather than a calculation. A
program that computes something can fail in two ways you cannot distinguish —
the apparatus is broken, or your logic is wrong. This one has no logic to get
wrong, which makes it the smallest question that still requires the whole
system to answer.

The thirteen characters are a receipt. Keep the machine; you are finished with
this document.

---

# Part 17: What To Do Next

## 17.1 Learn the language

| Resource | Notes |
|---|---|
| **Kernighan & Ritchie, *The C Programming Language*, 2nd ed.** | 272 pages. Still the best book on the language and one of the best technical books written. Start here. |
| **King, *C Programming: A Modern Approach*** | Longer, gentler, more exercises. Better as a first book for some readers. |
| **Gustedt, *Modern C*** | Free. Covers C17 and C23. Assumes some programming experience. |

## 17.2 Immediate next exercises

In rough order:

1. Print a second line
2. Print a number using `%d`
3. Read a number with `scanf` and print it back
4. Add two numbers
5. Write a loop that counts to ten
6. Write a function other than `main` and call it
7. Use an array
8. Use a pointer
9. Read a file
10. Write a program that takes a command-line argument

Item 8 is the one that separates C from most other languages, and it is worth
slowing down for.

## 17.3 Tools worth learning next

| Tool | What it does | When |
|---|---|---|
| `make` | Rebuilds only what changed | When you have more than one source file |
| `git` | Tracks changes to your code | **Now.** Before you need it. |
| `gdb` / `lldb` | Steps through a running program | When a program is wrong and you cannot see why |
| `valgrind` | Detects memory errors | Once you are using `malloc` |
| Sanitizers (`-fsanitize=address,undefined`) | Catches memory and undefined-behavior bugs at runtime | Immediately. Add them to every build while learning. |

The sanitizers deserve emphasis. Compiling with `-fsanitize=address,undefined`
turns a large class of silent, catastrophic C bugs into immediate, clear error
messages with line numbers. They cost some performance and they will save you
weeks.

## 17.4 A habit worth forming now

```bash
cd ~/code/hello
git init
git add hello.c
git commit -m "Initial commit"
```

Four commands. From this point every version of your work is recoverable. The
usual reason people do not do this is that their project seems too small to
warrant it, which is exactly when the habit is cheapest to form.

---

# Appendices

## Appendix A: Command Reference

| Command | Purpose |
|---|---|
| `pwd` | Print current directory |
| `ls` / `ls -l` / `ls -la` | List files / with detail / including hidden |
| `cd <dir>` / `cd ..` / `cd ~` | Change directory / up one / home |
| `mkdir -p <dir>` | Create a directory and any parents |
| `cat <file>` | Print a file |
| `less <file>` | Page through a file (`q` to quit) |
| `nano <file>` | Edit a file |
| `cp <a> <b>` | Copy |
| `mv <a> <b>` | Move or rename |
| `rm <file>` | Delete permanently. No undo. |
| `find ~ -name "<pattern>"` | Search for a file |
| `grep -n "<text>" <file>` | Find text in a file, with line numbers |
| `which <cmd>` | Show which program a name resolves to |
| `echo $PATH` | Show the program search path |
| `echo $?` | Show the last exit status |
| `chmod +x <file>` | Mark a file executable |
| `od -c <file>` | Show a file's exact bytes |
| `wc -l` / `wc -c` | Count lines / bytes |
| `man <cmd>` | Read the manual (`q` to quit) |

`man` is the one most often forgotten. Every command in this table has a manual
page on your machine, offline, written by the people who wrote the command.

## Appendix B: Compiler Flag Reference

| Flag | Effect |
|---|---|
| `-o <name>` | Name the output file |
| `-Wall` | Enable common warnings |
| `-Wextra` | Enable more warnings |
| `-Werror` | Treat warnings as errors |
| `-pedantic` | Warn on non-standard constructs |
| `-std=c99` / `-std=c11` / `-std=c17` | Select a language standard |
| `-O0` / `-O2` / `-O3` / `-Os` | Optimization: none / standard / aggressive / for size |
| `-g` | Include debug information |
| `-c` | Compile only; do not link |
| `-E` | Preprocess only |
| `-S` | Compile to assembly only |
| `-static` | Link the library statically |
| `-fsanitize=address,undefined` | Runtime error detection |
| `-I <dir>` | Add a directory to the header search path |
| `-l <name>` | Link against a library |

## Appendix C: Glossary

| Term | Meaning |
|---|---|
| **Binary / executable** | A file containing machine instructions, ready to run |
| **Compiler** | Translates source code into machine code |
| **Directive** | A preprocessor instruction, beginning with `#` |
| **Escape sequence** | Two or more source characters representing one character, e.g. `\n` |
| **Exit status** | An integer a program returns to whatever started it. `0` means success. |
| **Header** | A file of declarations, included into a source file |
| **Linker** | Combines compiled pieces into a single executable |
| **Literal** | A value written directly in the source, e.g. `"Hello"` or `0` |
| **`PATH`** | The list of directories the shell searches for programs |
| **Preprocessor** | A textual pass that runs before compilation |
| **Prompt** | The text the shell displays when awaiting a command |
| **Shell** | The program that interprets your typed commands |
| **Source code** | Text written by a person, intended to be compiled |
| **Standard library** | Functions supplied with every C implementation |
| **Statement** | A single instruction, terminated by `;` |
| **stdout** | Standard output; file descriptor 1; where `printf` writes |
| **Terminal** | The window in which a shell runs |
| **Toolchain** | The compiler, assembler, linker, and associated tools together |
| **Undefined behavior** | Program behavior on which the standard imposes no requirement whatsoever |

## Appendix D: Ergonomics Checklist

Run through this once, now, and again in a month.

- [ ] Feet flat on the floor, or on a footrest
- [ ] Knees at approximately 90 degrees
- [ ] Lower back supported by the chair or a cushion
- [ ] Shoulders relaxed, not raised
- [ ] Forearms roughly parallel to the floor
- [ ] Wrists straight, not bent up, down, or sideways
- [ ] Top of screen at or just below eye level
- [ ] Screen at arm's length
- [ ] No window directly behind the screen or directly behind you
- [ ] Room lighting roughly comparable to screen brightness
- [ ] A timer or habit that gets you standing every 30–45 minutes

The last item is the one that matters most and the one that is always skipped.
No chair, however expensive, protects against sitting still for six hours.

## Appendix E: A Note on Frustration

Some portion of readers will follow every step in this document and it will
still not work.

This is normal and it is not a reflection of aptitude. The failure will be
something small, specific, and locally invisible: a hidden file extension, a
curly quotation mark, a directory you are not in, a compiler installed for a
different architecture. Every one of these has stopped experienced engineers
for an hour.

The skill being learned here is not typing six lines of C. It is the process
in §15.15 — reading the error, checking assumptions with commands rather than
memory, and changing one thing at a time. That process is the entire job.
People who are good at this are not people who make fewer mistakes. They are
people who find their mistakes faster, and they got that way by making a great
many of them.

The program will run. It runs on everything.

---

**See also:** [README.md](README.md) for the project's technical documentation,
and [`hello.c`](hello.c) for the reasoning behind every decision in it.
