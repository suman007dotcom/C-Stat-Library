# C Statistics Library (From Scratch)

This project is a complete Statistics Library written in pure C, built from scratch without using any external libraries.

The main goal was to create a lightweight and efficient solution for statistical analysis, especially for embedded systems like ESP32, where high-level libraries like NumPy are not available.

## Why This Project
C does not have built-in statistical libraries like Python
Embedded systems cannot run heavy libraries
Building from scratch helps in deeply understanding statistical concepts
## Features
1. Descriptive Statistics
Mean (average of data)
Median (middle value after sorting)
Mode (most frequent value)
Range (difference between max and min)
2. Measures of Dispersion
Variance (with Bessel’s correction)
Standard Deviation
Mean Deviation (from mean or median)
3. Distribution Shape
Moments (2nd, 3rd, 4th order)
Skewness (data symmetry)
Kurtosis (data peak/flatness)
4. Quartile Analysis
Q1, Q2 (median), Q3
IQR (Interquartile Range)
Quartile Deviation
## Correlation & Regression
1. Correlation
Covariance
Pearson Correlation Coefficient
R² (coefficient of determination)
2. Linear Regression
Slope (Y on X and X on Y)
Intercept
Predict Y using X
Predict X using Y
## Outlier Detection
3-Sigma Rule
Median Absolute Deviation (MAD)
Boxplot Method (IQR based)
## Error Metrics
MAE (Mean Absolute Error)
RMSE (Root Mean Square Error)
MAPE (Mean Absolute Percentage Error)
## Inferential Statistics
Point Estimate (sample mean)
Confidence Interval (using Z values like 1.96 for 95%)
## Project Structure
stat.h → function declarations and struct definitions
stat.c → full implementation of all functions
Student_per.c → analysis on student dataset
sensor.c → analysis on IoT sensor dataset
## Real Dataset Testing
1. Student Performance Dataset
Reading & Writing → very strong correlation (~0.95)
Math & Reading → strong correlation (~0.82)
Lunch type affects performance
Parental education has weak impact
2. Classroom Sensor Dataset
Engagement → strongest factor (~0.89)
Noise → negatively affects learning
Temperature → almost no effect
## Limitations
Bubble sort used → slow for large datasets
Stack memory issues with large arrays
No NaN/Inf validation
Mode not useful for float data
Arduino has limited output functions
## How to Run
Open project folder in VS Code
Open terminal
Navigate to folder

Compile using:
gcc sensor.c stat.c -o run
.\run
## Conclusion
Built 33 statistical functions across 5 units
Fully written in pure C with zero dependencies
Works on real datasets (1000+ entries)
Compatible with embedded systems like ESP32
Helps in understanding both statistics + low-level programming deeply
### Dataset Links
https://www.kaggle.com/datasets/spscientist/students-performance-in-exams
https://www.kaggle.com/datasets/ziya07/smart-classroom-iot-edge-dataset
### GitHub Repo
https://github.com/suman007dotcom/C-Stat-Library
