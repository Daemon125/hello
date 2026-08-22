#!/usr/bin/env python3
"""Verify every link and cross-reference in the repository's documentation.

Three classes of reference are checked:

  1. Intra-document anchors  [text](#anchor)  must match a heading in the
     same file, using GitHub's slug algorithm.
  2. Relative file links     [text](path)     must name a file that exists.
  3. Source cross-references "section N.N" / "§N.N" appearing in the
     Markdown must correspond to a section that exists in hello.c.

Exits 0 if every reference resolves, 1 otherwise.
"""
import re
import sys
import pathlib

ROOT = pathlib.Path(__file__).resolve().parent.parent
DOCS = [
    "README.md",
    "INSTRUCTIONS.md",
    "INSTALL.md",
    "UNINSTALL.md",
    "CONTRIBUTING.md",
    "SECURITY.md",
    "SUPPORT.md",
    "CHANGELOG.md",
    "CODE_OF_CONDUCT.md",
]

failures = []
checked = 0


def slug(heading: str) -> str:
    """GitHub's heading-to-anchor transformation."""
    s = heading.strip().lower()
    s = re.sub(r"<kbd>|</kbd>|`|\*|_", "", s)
    s = re.sub(r"[^\w\s-]", "", s)
    return re.sub(r"\s+", "-", s).strip("-")


def headings(text: str) -> set:
    out = set()
    for line in text.splitlines():
        m = re.match(r"^(#{1,6})\s+(.*)$", line)
        if m:
            out.add(slug(m.group(2)))
    return out


# hello.c is organized as "N.N  Title" inside block comments.
source = (ROOT / "hello.c").read_text(encoding="utf-8", errors="replace")
src_sections = set(re.findall(r"^\s*\*\s+(\d+\.\d+)\s+\S", source, re.M))

for name in DOCS:
    path = ROOT / name
    if not path.exists():
        failures.append(f"{name}: missing")
        continue
    text = path.read_text(encoding="utf-8")
    anchors = headings(text)

    for label, target in re.findall(r"\[([^\]]+)\]\(([^)]+)\)", text):
        checked += 1
        if target.startswith(("http://", "https://", "mailto:")):
            continue
        # GitHub resolves ../../issues/... and ../../pulls/... relative to
        # the repository rather than the file tree, and a query string is
        # never part of a path. Neither corresponds to a file on disk.
        if target.startswith("../../") or "?" in target:
            continue
        if target.startswith("#"):
            if target[1:] not in anchors:
                failures.append(f"{name}: dead anchor [{label}]({target})")
        else:
            ref = (ROOT / target.split("#")[0]).resolve()
            if not ref.exists():
                failures.append(f"{name}: dead file link [{label}]({target})")

    for ref in re.findall(r"(?:§|[Ss]ection )(\d+\.\d+) of (?:the source|`?hello\.c`?)", text):
        checked += 1
        if ref not in src_sections:
            failures.append(f"{name}: references hello.c section {ref}, which does not exist")

# README cites specific source sections in prose without the trailing
# "of the source"; catch the ones that name hello.c nearby.
readme = (ROOT / "README.md").read_text(encoding="utf-8")
for ref in re.findall(r"see §(\d+\.\d+) of \[`hello\.c`\]", readme):
    checked += 1
    if ref not in src_sections:
        failures.append(f"README.md: references hello.c section {ref}, which does not exist")

print(f"    {checked} references checked, {len(src_sections)} source sections indexed")
for f in failures:
    print(f"    DEAD: {f}")

sys.exit(1 if failures else 0)
