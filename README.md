# Huffman Coding

A small C project implementing the construction of a Huffman tree from a text file, with frequency and intermediate structure display.

## 🚀 Features

- Read a text file and count character occurrences (ASCII 0–255)
- Initialize the Huffman structure and nodes (leaves + internal)
- Sort nodes by occurrence (then by lexicographic order)
- Incrementally build the tree (merge the two smallest nodes)
- Useful displays for debugging/visualization

## 📦 Project Structure

```text
.
├── data/
│   └── data.txt           # Sample input file
├── inc/
│   ├── dot.h              # DOT/PDF export helpers (Graphviz)
│   ├── file.h             # File I/O
│   ├── huffman.h          # Huffman structures & API
│   ├── loop.h             # Build loop
│   └── print.h            # Display helpers
├── src/
│   ├── dot.c              # DOT/PDF export
│   ├── file.c             # File helpers (openFile)
│   ├── huffman.c          # Algorithm core
│   ├── loop.c             # Orchestration
│   ├── main.c             # Entry point (writes out/huffman.{dot,pdf})
│   └── print.c            # Display implementations
├── sujet/
│   └── 8-huffman.pdf      # Assignment statement
├── makefile               # GCC build
└── README.md              # This document
```

## 🛠️ Build

Make sure you have GCC installed.

```bash
make all
```

The generated binary is named `huffman`.

## ▶️ Run

The program reads `data/data.txt` by default and writes visualization files under `out/`.

```bash
make run
```

Or directly:

```bash
./huffman

On each run, the program will:
- Ensure the `out/` directory exists
- Generate `out/huffman.dot` (Graphviz DOT)
- Try to generate `out/huffman.pdf` (requires Graphviz `dot` on your PATH)

If Graphviz is missing, only the DOT file will be produced, and a warning will be printed.
```

## ✏️ API usage

- Open input via `openFile()` in `fichier.c` (`file.h`).
- Collect frequencies with `storeOccurrences(FILE*)` (implemented in `huffman.c`, declared in `huffman.h` and `file.h`).
- `countLetters()` computes the number of distinct characters found.
- `initHuffman()` + `initNodes()` initialize the structures.
- `sortNodes()` sorts nodes by occurrence (then by ASCII code).
- `growTree()` merges the two minimal nodes to grow the tree.
- `displayHuffman()` and `displayOccurrences()` print the current state.

Tip: the build loop continues until the number of nodes reaches `2 * nbLeaves - 1` (in code: `while (huffman.nbNodes < huffman.capacity)`), which produces a full Huffman tree.

## 🔁 Useful Make targets

- `make all`: build
- `make run`: run the program
- `make clean`: clean objects and binary
- `make help`: help

## ✅ Requirements

- GCC
- POSIX environment (Linux/macOS). Tested on Linux.
- Optional: Graphviz (`dot`) for PDF output.

## 📚 Notes

- The project handles 256 symbols (`CHARACTER_COUNT`). Non-printable characters may appear in results.
- You can modify `data/data.txt` to test other corpora.

## ❗ Troubleshooting

- If the binary doesn’t launch: check permissions (`chmod +x huffman`) and the existence of `data/data.txt`.
