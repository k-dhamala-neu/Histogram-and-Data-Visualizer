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

### Other Included Files
The `tests/waveform_lab.csv` file is an additional dataset that can be loaded in `main.cpp` 
and was obtained from actual physics lab data.
