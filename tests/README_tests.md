# Test Cases

## Test 1 — Simple Distribution (test.csv)
Run test case by selecting choice 5 from the program menu.

### Dataset Description
A 20 point dataset with y values rising from 1.5 to 8.5 over time, 
with value 4.2 appearing most frequently.

### Input File
`tests/test.csv`
```
Time (us),Waveform 1
1.0,1.5
2.0,2.3
3.0,2.3
4.0,3.1
5.0,3.1
6.0,3.1
7.0,4.2
8.0,4.2
9.0,4.2
10.0,4.2
11.0,5.0
12.0,5.0
13.0,5.0
14.0,5.8
15.0,5.8
16.0,6.5
17.0,6.5
18.0,7.1
19.0,7.8
20.0,8.5
```

### Expected Console Output
```
Data size: 20

--- Statistics ---
Mean: 4.76
Median: 4.6
Mode: 4.2
Std Dev: 1.8621
Variance: 3.4674
Max: (20, 8.5)
Min: (1, 1.5)
```

### Statistical Output Explanation
| Output | Value | Explanation |
|--------|-------|-------------|
| Mean | 4.76 | Average of all 20 y values |
| Median | 4.6 | Middle value when all y values are sorted |
| Mode | 4.2 | Most frequent value, appearing 4 times |
| Std Dev | 1.8621 | Spread of y values around the mean |
| Variance | 3.4674 | Square of the standard deviation |
| Max | (20, 8.5) | Highest y value of 8.5 occurs at x = 20 |
| Min | (1, 1.5) | Lowest y value of 1.5 occurs at x = 1 |

### Expected Histogram Output
```
           x                            
           x                            
           x                            
           x               x            
   x       x       x       x       x    
   x       x       x       x       x    
   x       x       x       x       x    
Bin 1   Bin 2   Bin 3   Bin 4   Bin 5  
```

### Histogram Bin Explanation
| Bin | Range | Frequency | Explanation |
|-----|-------|-----------|-------------|
| Bin 1 | 1.5 - 2.9 | 3 | Values 1.5, 2.3, 2.3 |
| Bin 2 | 2.9 - 4.3 | 7 | Values 3.1, 3.1, 3.1, 4.2, 4.2, 4.2, 4.2 |
| Bin 3 | 4.3 - 5.7 | 3 | Values 5.0, 5.0, 5.0 |
| Bin 4 | 5.7 - 7.1 | 4 | Values 5.8, 5.8, 6.5, 6.5 |
| Bin 5 | 7.1 - 8.5 | 3 | Values 7.1, 7.8, 8.5 |

### Histogram Image Output
The histogram image is saved to `images/histogram.png` and shows a distribution 
with the tallest bar in Bin 2 (2.9-4.3) with a frequency of 7, reflecting that 
most y values are concentrated in the lower-middle range of the dataset.

### Histogram Settings
| Setting | Value |
|---------|-------|
| Number of bins | 5 |
| Bin size | 1.4 |
| Output file | `images/histogram.png` |

**Note:** The lineplot image `images/lineplot.png` was generated with the data from the `tests/test.csv` file.


## Test 2 — Insurance Dataset (has_insurance.csv)

### Dataset Description
A 100 point real-world dataset representing patient ages (x) and whether they have insurance (y = 1) or not (y = 0).

### Input File
`tests/has_insurance.csv`

### Expected Output
After loading the file successfully with 100 data points, the statistics show a mean of 0.44 indicating 44% of patients have insurance. The median is 0 meaning more than half do not have insurance, and the mode is 0 confirming no insurance is the most common value. Standard deviation is 0.496387 and variance is 0.2464. The maximum value of 1 occurs at x=56 and the minimum value of 0 occurs at x=32. Since y values are binary (0 or 1), setting bin count to 2 via option 7 produces a cleaner histogram showing the split between insured and uninsured patients.

### Statistical Output Explanation
| Output | Value | Explanation |
|--------|-------|-------------|
| Mean | 0.44 | 44% of patients have insurance |
| Median | 0 | More than half do not have insurance |
| Mode | 0 | Most common value; no insurance |
| Std Dev | 0.496387 | Spread of binary values around mean |
| Variance | 0.2464 | Square of standard deviation |
| Max | (56, 1) | Patient aged 56 has insurance |
| Min | (32, 0) | Patient aged 32 does not have insurance |

---

## Test 3 — Simple Distribution TXT (test.txt)
Same dataset as `tests/test.csv` but in `.txt` format with space delimiter. Used to verify `.txt` file loading works correctly. Expected output is identical to Test 1.

---

## Test 4 — Waveform Lab Data (waveform_lab.csv)
Real physics lab waveform data with extremely small y values approaching zero. Used to verify log scale detection and out of range value handling. Due to the extreme value range, the line plot automatically switches to log scale when exported. Histogram is not recommended due to the magnitude of the y-values.

---

## Edge Cases

### EC1 — Empty File (edge_cases/empty.txt)
A file with no data rows. The program correctly identifies the file as empty and returns an error without crashing.

**Expected Output:**
File opens successfully but returns "File has no data" since no valid data rows exist. The program then attempts `.txt` and `.csv` extensions as fallback before reporting the file was unable to be loaded.

---

### EC2 — Single Data Point (edge_cases/single.csv)
A file with exactly one data row. Tests behavior of all statistical methods with minimal data.

**Expected Output:**
Loads with data size of 1. Mean, median, and mode all return the single y value of 3.5. Standard deviation and variance are both 0 since there is no spread. Max and min return the same point (5, 3.5). Histogram displays one x marker in Bin 1.

**Note:** Mode returning the single value is a known design decision — a single value dataset has no true mode but the program returns the only available value.

---

### EC3 — Identical Values (edge_cases/identical.csv)
A dataset where all 9 y values are identical (5.0) with x values ranging from 1 to 10.

**Expected Output:**
Loads with data size of 9. Mean, median, and mode all return 5. Standard deviation and variance are both 0. Max and min both return (1, 5) since all y values are equal and the position never updates from index 0. Histogram places all 9 values in Bin 1 with range defaulting to 1.

---

### EC4 — Negative Values (edge_cases/negative.txt)
A 20 point dataset with y values ranging from -5.0 to 9.5. Tests that statistics and histogram handle negative values correctly.

**Expected Output:**
Loads with data size of 20. Mean is 1.47, median is 0.75, mode is 0 appearing 4 times, standard deviation is 3.797, and variance is 14.417. Max is (20, 9.5) and min is (1, -5). Histogram correctly handles negative bin ranges.

---

### EC5 — String Data (edge_cases/string.txt)
A file containing only non-numeric string values. Tests that the program handles invalid data gracefully.

**Expected Output:**
Each non-numeric row triggers "Warning: Incomplete or invalid data at line 1, skipping." After all rows are skipped the program returns "File has no data" and reports the file was unable to be loaded.

**Note:** The repeated text of "... line 1, skipping." is correct since the line count only increases after a successful line read, meaning 1 never increments to a new value.

---

### EC6 — Three Column File (edge_cases/three_column.txt)
A file with three columns of data. Tests that the program correctly uses only x and y columns and warns about extra data.

**Expected Output:**
Loads with data size of 3 after printing once: "Warning: Extra columns detected, only x and y values will be used." Statistics are computed correctly from the first two columns only. Mean is 5, mode is No Mode, std dev is 2.44949, max is (7, 8), min is (1, 2).

---

### EC7 — Filename with Spaces (edge_cases/space in fname.csv)
A file with spaces in the filename. Tests that `getline` correctly reads the full path including spaces.

**Expected Output:**
Loads successfully with data size of 20 using the same data as test.csv. Demonstrates that file paths with spaces are handled correctly by `getline(cin, chosenfPath)`.
