#!/usr/bin/env python3
"""Verify that numbered section headings are dense and unique.

The documents in this repository are cross-referenced by section number,
by each other and by the test suites. A heading that is duplicated, or a
number that is skipped, breaks those references silently: nothing fails to
build, and a reader following "see section 11.9" arrives nowhere.

This is not hypothetical. Inserting a section immediately before an
existing one, and renumbering the existing one out of the way, left
README.md with 11.8 followed by 11.10 and no 11.9. Nothing detected it.

For every document, this checks that:

  - no section number appears twice
  - within each parent, numbering starts at 1
  - within each parent, numbering increments by exactly 1

Exits 0 if every document is consistent, 1 otherwise.
"""
import re
import sys
import pathlib
from collections import defaultdict

ROOT = pathlib.Path(__file__).resolve().parent.parent
DOCS = ["README.md", "INSTRUCTIONS.md", "INSTALL.md", "UNINSTALL.md"]

# Matches "## 11", "### 11.9", "#### 1.10.2" and captures the full number.
HEADING = re.compile(r"^#{2,4}\s+(\d+(?:\.\d+)*)\s")

failures = []
counted = 0

for name in DOCS:
    path = ROOT / name
    if not path.exists():
        failures.append(f"{name}: missing")
        continue

    numbers = []
    for line in path.read_text(encoding="utf-8").splitlines():
        m = HEADING.match(line)
        if m:
            numbers.append(m.group(1))

    seen = set()
    last = defaultdict(lambda: None)

    for num in numbers:
        counted += 1
        if num in seen:
            failures.append(f"{name}: section {num} appears more than once")
        seen.add(num)

        parts = num.split(".")
        parent = ".".join(parts[:-1])
        n = int(parts[-1])
        prev = last[parent]

        if prev is None:
            if n != 1:
                where = f"{parent}.x" if parent else "top level"
                failures.append(
                    f"{name}: {where} starts at {num}, expected {parent + '.' if parent else ''}1"
                )
        elif n != prev + 1:
            gap = f"{parent + '.' if parent else ''}{prev}"
            failures.append(f"{name}: section {num} follows {gap} -- a number is skipped")

        last[parent] = n

    print(f"    {name}: {len(numbers)} numbered sections")

for f in failures:
    print(f"    BAD: {f}")

sys.exit(1 if failures else 0)
