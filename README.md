# C-Stat-Library
# Statistics Library in C

This project is a complete **statistics library built in pure C**. All functions are implemented from scratch, from basic operations like square root to advanced concepts like regression and correlation. **No external libraries are used.**

The main goal of this project was to **understand statistics deeply** by implementing every concept manually. Instead of relying on ready-made tools, each formula is translated into logic using C. This makes the concepts clearer and more practical.

Another important purpose is usability in **embedded systems**. Languages like Python with libraries such as NumPy are not supported on devices like ESP32 or Arduino. This library is **lightweight, efficient, and suitable for such environments.**

---

## What the library includes

### Descriptive statistics
- mean, median, mode, range  
- variance, standard deviation, mean deviation  

### Advanced concepts
- moments, skewness, kurtosis  
- quartile analysis (Q1, Q2, Q3, IQR)  

### Correlation and regression
- covariance, Pearson correlation  
- slope, intercept  
- prediction functions  

### Outlier detection
- 3-sigma rule  
- MAD method  
- IQR / boxplot  

### Error metrics
- MAE, RMSE, MAPE  

### Inferential statistics
- point estimate  
- confidence interval  

---

## Project structure

- **stat.h** contains function declarations  
- **stat.c** contains implementation  
- other files like **student_per.c** and **sensor.c** use the library  

---

## Key points

- everything is written **from scratch**  
- **no external dependencies**  
- works on **low-resource systems**  
- focus on both **learning and practical use**  

---

## Testing

The library was tested on real datasets including student performance data and classroom sensor data. It helped find patterns like strong correlation between reading and writing scores and the impact of engagement on learning.

---

## How to run

```bash
gcc test.c stat.c -o output
./output
