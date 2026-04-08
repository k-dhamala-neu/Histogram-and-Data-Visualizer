# Statistical Analysis and Histogram Generator

## Team Members
- Krish Dhamala
- Daniel Gutierrez
- Hue Gomatam

## Project Overview
A C++ application that reads numerical datasets from `.csv` or `.txt` files and performs 
statistical analysis and graph generation. Histograms and line plots are automatically 
exported and visualized using gnuplot, with output images saved to the `images/` folder.

## Main Functionalities
- **Dataset Loading** — Reads `.csv` or `.txt` files and stores data as (x, y) pairs. Automatically detects delimiter, skips headers, and validates input
- **Statistics Calculator** — Computes mean, median, mode, standard deviation, variance, min, and max
- **Histogram Generator** — Generates a text-based histogram in the console with configurable bin count and size
- **Histogram Export** — Exports histogram data and automatically plots it using gnuplot, saving the image to `images/histogram.png`. Labels rotate automatically for larger bin counts
- **Line Plot Export** — Exports an x vs y line plot via gnuplot, saved to `images/lineplot.png`. Automatically switches to log scale for datasets with very small y values
- **Interactive Menu** — Menu driven interface with input validation for all user inputs

## System Design
![System Overview](images/system_diagram.png)

## OOP Design Summary
| Class | Responsibility |
|-------|---------------|
| `Dataset` | Loads and stores data from file as (x,y) DataPoints |
| `Histogram` | Computes bin ranges, frequencies, and exports to gnuplot |
| `Statistics` | Computes statistical measures from the dataset |

## Tools and Technologies
- C++ (C++17)
- gnuplot 6.0
- WSL Ubuntu
- VS Code

## Folder Structure
```
Project/
│
├── README.md
├── .gitignore
├── docs/
│   └── system_design_overview.pdf
├── pseudocode/
│   └── pseudocode.pdf
├── src/
│   ├── main.cpp
│   ├── Dataset.h
│   ├── Dataset.cpp
│   ├── Histogram.h
│   ├── Histogram.cpp
│   ├── StatsCalc.h
│   └── StatsCalc.cpp
├── tests/
│   ├── test.csv
│   ├── test.txt
│   ├── has_insurance.csv
│   ├── waveform_lab.csv
│   ├── README_tests.md
│   └── edge_cases/
│       ├── empty.txt
│       ├── single.csv
│       ├── identical.csv
│       ├── negative.txt
│       ├── string.txt
│       ├── three_column.txt
│       └── space in fname.csv
└── images/
├── system_diagram.png
├── histogram.png
└── lineplot.png
```

## Run Procedure
**Dependencies:**
```bash
sudo apt-get install gnuplot
```

**Compile:**
```bash
g++ src/main.cpp src/Dataset.cpp src/Histogram.cpp src/StatsCalc.cpp -o main -Wall -Wextra -Wpedantic
```

**Run:**
```bash
./main
```

## Menu Options
| Option | Description |
|--------|-------------|
| 1 | Load a `.csv` or `.txt` file by file path |
| 2 | Display statistical analysis of loaded dataset |
| 3 | Generate text-based histogram in console |
| 4 | Export histogram image via gnuplot |
| 5 | Run built-in test case with `tests/test.csv` |
| 6 | Change bin size for histogram |
| 7 | Change number of bins for histogram |
| 8 | Export line plot image via gnuplot |
| 9 | Exit program |

## Test Cases
Multiple test datasets are provided in the `tests/` folder including real-world data and edge cases.

| File | Description |
|------|-------------|
| `tests/test.csv` | Simple distribution dataset with 20 data points |
| `tests/test.txt` | Same as test.csv in `.txt` format |
| `tests/has_insurance.csv` | 100 point real-world insurance dataset |
| `tests/waveform_lab.csv` | Physics lab waveform data with extreme value range |
| `tests/edge_cases/` | Edge case files for robustness testing |

To run the built-in test case, select option 5 from the program menu.
Full expected outputs and explanations are documented in `tests/README_tests.md`.

## What Has Been Implemented
- Full `Dataset` class with CSV/TXT file loading, delimiter detection, and input validation
- Full `Statistics` class with all statistical computations including NaN handling for mode
- Full `Histogram` class with text-based display, configurable bins, and gnuplot export
- Line plot export with automatic log scale detection for small y values
- Interactive menu system with full input validation
- Edge case handling for empty files, identical values, negative values, string data, and extra columns
- Clean build with zero compiler warnings under `-Wall -Wextra -Wpedantic`

## Project Goals
- Provide a simple tool for analyzing time-series or waveform datasets typically used in physics lab settings
- Display statistical summaries clearly in the console
- Generate publication-quality histogram and line plot images automatically
- Export images for use in reports and presentations
- Demonstrate input validation and edge case handling

## AI Usage
This project utilized AI assistance (Claude by Anthropic) in the following ways:

- **Debugging** — Identifying and resolving runtime errors and logical bugs in C++ code
- **Concept Explanation** — Clarifying C++ concepts outside of course material such as 
   structs, advanced file I/O, and gnuplot integration
- **Documentation Formatting** — Assistance with LaTeX formatting for pseudocode and 
  system design documents, and structuring the README

All core logic, design decisions, and implementation were completed by the team. 
AI was not used to write functional code directly.

## Github Commits
Team members experienced issues pulling, pushing, and committing changes from cloned repositories. 
As a workaround, updated files were sent directly to the repository owner to push. This is why 
there is a disproportionate number of commits from one user and why some contributors do not appear 
in the GitHub contributor graph despite their contributions to the project.