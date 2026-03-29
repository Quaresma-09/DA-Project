# Conference Assignment System — DA Project 1

## Description

Tool for assigning scientific conference paper submissions to reviewers using **Maximum Flow** (Edmonds-Karp algorithm). Developed for the Design of Algorithms (DA) course at FEUP, Spring 2026.

The system formulates reviewer-submission assignment as a network flow problem and supports risk analysis to identify critical reviewers.

## Features

- **CSV Parsing**: Reads submissions, reviewers, parameters and control settings from structured CSV files.
- **Max-Flow Assignment**: Uses Edmonds-Karp (O(V·E²)) to compute optimal reviewer-submission assignments.
- **Multiple Assignment Modes**: Supports primary-only (mode 1), primary+secondary submission domains (mode 2), and full domain matching (mode 3).
- **Risk Analysis (K=1)**: Identifies critical reviewers whose absence would make valid assignment impossible.
- **Interactive CLI Menu**: User-friendly menu for loading data, viewing results, and running analysis.
- **Batch Mode**: Scriptable execution via `./myProg -b input.csv output.csv`.

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

### Interactive Mode
```bash
./myProg
```

### Batch Mode
```bash
./myProg -b data/input/dataset1.csv output.csv
```

## Project Structure

```
├── include/
│   ├── model/          # Submission, Reviewer, Config classes
│   ├── parser/         # CsvParser
│   ├── graph/          # Graph, MaxFlow (Edmonds-Karp)
│   ├── core/           # AssignmentEngine, RiskAnalyzer, OutputWriter
│   └── ui/             # Menu
├── src/                # Implementations (.cpp)
├── data/
│   ├── input/          # Input datasets
│   ├── output/         # Expected outputs
│   └── risk/           # Expected risk analysis outputs
└── docs/               # Generated Doxygen documentation
```

## Flow Network Model

```
Source → [Reviewer nodes] → [Submission nodes] → Sink
```

- **Source → Reviewer**: capacity = `MaxReviewsPerReviewer`
- **Reviewer → Submission**: capacity = 1 (if expertise matches domain)
- **Submission → Sink**: capacity = `MinReviewsPerSubmission`

## Documentation

Generate Doxygen documentation:
```bash
doxygen Doxyfile
```
Output will be in `docs/html/`.

## Authors

- Diogo Afonso (up202406470)
- Gonçalo Quaresma (up202407377)
- Francisco Antunes (up202307639)

DA 2026 — L.EIC016, FEUP