#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stat.h"

#define MAX_ROWS 1000

void strip_quotes(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != '\"') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    FILE *fp = fopen("StudentsPerformance.csv", "r");
    if (fp == NULL) {
        printf("Error: StudentsPerformance.csv not found in this folder!\n");
        return 1;
    }

    char gender[MAX_ROWS][20];
    char race[MAX_ROWS][20];
    char parent_edu[MAX_ROWS][50];
    char lunch[MAX_ROWS][20];
    char prep_course[MAX_ROWS][20];
    double math[MAX_ROWS];
    double reading[MAX_ROWS];
    double writing[MAX_ROWS];

    char line[1024];
    int count = 0;

    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) && count < MAX_ROWS) {
        char *token;
        int col = 0;

        token = strtok(line, ",");
        while (token != NULL) {
            strip_quotes(token); 

            if (col == 0) strcpy(gender[count], token);
            if (col == 1) strcpy(race[count], token);
            if (col == 2) strcpy(parent_edu[count], token);
            if (col == 3) strcpy(lunch[count], token);
            if (col == 4) strcpy(prep_course[count], token);
            if (col == 5) math[count] = atof(token);
            if (col == 6) reading[count] = atof(token);
            if (col == 7) writing[count] = atof(token);

            token = strtok(NULL, ",");
            col++;
        }
        count++;
    }
    fclose(fp);

    printf("Successfully extracted 8 columns for %d students.\n", count);
    printf("-----------------------------------------------------------\n");

    printf("%-7s | %-15s | %-10s | %-4s | %-4s\n", "GENDER", "PARENT_EDU", "PREP", "MATH", "READ");
    printf("-----------------------------------------------------------\n");
    for (int j = 0; j < 5; j++) {
        printf("%-7s | %-15.15s | %-10s | %-4.0f | %-4.0f\n", 
               gender[j], parent_edu[j], prep_course[j], math[j], reading[j]);
    }

    printf("\n--- CLASS STATISTICS (%d Students) ---\n", count);
    printf("Math Average:    %.2f\n", mean(math, count));
    printf("Math StdDev:     %.2f\n", std_dev(math, count));

    double total_pct[MAX_ROWS], gender_num[MAX_ROWS];
    double m_scores[MAX_ROWS], f_scores[MAX_ROWS];
    int m_cnt = 0, f_cnt = 0;

    for(int j=0; j<count; j++) {
        total_pct[j] = (math[j] + reading[j] + writing[j]) / 3.0;
        if(strcmp(gender[j], "female") == 0) {
            gender_num[j] = 1.0;
            f_scores[f_cnt++] = total_pct[j];
        } else {
            gender_num[j] = 0.0;
            m_scores[m_cnt++] = total_pct[j];
        }
    }
// for fun
    printf("\n--- THE GENDER BATTLE ---\n");
    double m_avg = mean(m_scores, m_cnt);
    double f_avg = mean(f_scores, f_cnt);
    printf("Male Avg Total:   %.2f%%\n", m_avg);
    printf("Female Avg Total: %.2f%%\n", f_avg);
    printf("Result: %s are smarter overall.\n", (f_avg > m_avg ? "Females" : "Males"));

    printf("\n--- CORRELATION ANALYSIS ---\n");
    printf("Gender vs Score Correlation: %f\n", corr(gender_num, total_pct, count));

// Lets corr between parent education and marks of student
// --- 1. CONVERT PARENT EDU TO NUMERIC RANKS ---
    double edu_rank[MAX_ROWS];

    for(int j = 0; j < count; j++) {

        // Assign Rank based on the text
        if      (strcmp(parent_edu[j], "some high school") == 0)    edu_rank[j] = 1.0;
        else if (strcmp(parent_edu[j], "high school") == 0)         edu_rank[j] = 2.0;
        else if (strcmp(parent_edu[j], "some college") == 0)        edu_rank[j] = 3.0;
        else if (strcmp(parent_edu[j], "associate's degree") == 0)  edu_rank[j] = 4.0;
        else if (strcmp(parent_edu[j], "bachelor's degree") == 0)   edu_rank[j] = 5.0;
        else if (strcmp(parent_edu[j], "master's degree") == 0)     edu_rank[j] = 6.0;
        else edu_rank[j] = 0.0; // Fallback for safety
    }

    // --- 2. RUN THE CORRELATION ---
    printf("\n--- MARKS VS PARENTS EDUCATION ---\n");
    
    double education_correlation = corr(edu_rank, total_pct, count);
    
    printf("Correlation Result: ");
    corr(edu_rank, total_pct, count);
    // --- 3. INTERPRETATION ---
    if (education_correlation > 0) {
        printf("Insight: There is a POSITIVE relationship. As parents education level increases, student marks tend to go up.\n");
    } else if (education_correlation < 0) {
        printf("Insight: There is a NEGATIVE relationship. Parents education level does not seem to help marks in this data.\n");
    } else {
        printf("Insight: No relationship found.\n");
    }

    // Since the corr is weak so the saying "there is a relationship" most likely to be a myth

    // Lets see how much it increases using slope
    double m = slope(edu_rank, total_pct, count);
    printf("Slope (Increase per Edu Level): %.2f points\n", m);

//-------- Lets check rest of functions ----- 

    printf("Median:          %.2f\n", median(math, count));
    printf("Mode:            %.2f\n", mode(math, count));
    printf("Range:           %.2f\n", range(math, count));
    printf("Variance:        %.2f\n", var(math, count));
 
// mean deviation - it shows both (mean and median based), intern takes med_mean=1 for mean
    printf("Mean Deviation (from mean):   ");
    mean_deviation(math, count, 1);
    printf("\n");
    printf("Mean Deviation (from median): ");
    mean_deviation(math, count, 0);
    printf("\n");
 
// quartiles of math - Q1 Q2 Q3 IQR QD
    printf("\n--- QUARTILE--\n");
    QuartileResult qmath = Quartile(math, count);
 
// skewness 
    printf("\n--- IS MATH SCORE DISTRIBUTION SKEWED? ---\n");
    printf("Skewness (moment method): %.4f  -> ", skewness(math, count));
    printf("Skewness Coeff (using median): %.4f\n", skewnesscoeff(math, count, 1));
    printf("Skewness Coeff (using mode):   %.4f\n", skewnesscoeff(math, count, 0));
 
// kurtosis - sharp peak or flat?
    printf("\n--- KURTOSIS OF MATH SCORES ---\n");
    printf("Kurtosis (beta2):   %.4f  -> ", kurtosis(math, count));
    printf("Excess Kurtosis:    %.4f\n", kur_coeff(math, count));
 
// --- OUTLIER DETECTION ---
    printf("\n--- OUTLIER CHECK: MATH SCORES (3-Sigma Rule) ---\n");
    int found1 = three_sigma(math, count);
    if(found1 == 0) printf("No outliers found. Everyone is normal i guess.\n");
 
    printf("\n--- OUTLIER CHECK: MATH SCORES (Boxplot / IQR Method) ---\n");
    int found2 = boxplot_bound(math, count);
    if(found2 == 0) printf("No outliers found using boxplot method.\n");
 
// MAD - median absolute deviation
    printf("\n--- MAD (Median Absolute Deviation) of Math ---\n");
    printf("MAD: %.4f\n", Mad(math, count));
 
// lets check if a specific score is an outlier using MAD
// i will check score = 0 (some student got 0, is that actually weird or not)
    printf("Is score=0 an outlier by MAD? %s\n", mad_outlier(0.0, math, count) ? "YES outlier" : "No, not outlier");
    printf("Is score=100 an outlier by MAD? %s\n", mad_outlier(100.0, math, count) ? "YES outlier" : "No, not outlier");
 
// --- MOMENTS ---
// 1st moment is always 0, 2nd is variance basically, 3rd is skewness related
    printf("\n--- MOMENTS OF MATH DISTRIBUTION ---\n");
    printf("1st moment (should be ~0): %.6f\n", moment(math, count, 1));
    printf("2nd moment (variance):     %.4f\n",  moment(math, count, 2));
    printf("3rd moment:                %.4f\n",  moment(math, count, 3));
    printf("4th moment:                %.4f\n",  moment(math, count, 4));
 
// --- REGRESSION: predict math score from reading score ---
// reading and math are probably related, lets see
    printf("\n--- REGRESSION: PREDICT MATH FROM READING ---\n");
    printf("R-squared (how good the prediction is): %.4f\n", r_squared(reading, math, count));
    printf("Intercept: %.4f\n", intercept(reading, math, count));
    printf("Slope (b_yx): %.4f\n", slope(reading, math, count));
 
// predict math if reading = 70
    double predicted_math = predict_y(70.0, reading, math, count);
    printf("If reading score = 70, predicted math = %.2f\n", predicted_math);
 
// predict math if reading = 90
    predicted_math = predict_y(90.0, reading, math, count);
    printf("If reading score = 90, predicted math = %.2f\n", predicted_math);
 
// reverse regression - predict reading from math
    printf("\n--- REVERSE: PREDICT READING FROM MATH ---\n");
    double predicted_reading = predict_x(75.0, reading, math, count);
    printf("If math score = 75, predicted reading = %.2f\n", predicted_reading);
 
// --- WRITING vs READING correlation ---
    printf("\n--- WRITING vs READING CORRELATION ---\n");
    double wr_corr = corr(writing, reading, count);
    printf("Covariance (writing, reading): %.4f\n", cov(writing, reading, count));
    // corr already printed the strength above
 
// --- ERROR METRICS: how good is our regression prediction? ---
// make predicted array first using the regression line we made
    printf("\n--- MODEL ACCURACY: MATH PREDICTED FROM READING ---\n");
    double math_predicted[MAX_ROWS];
    double b_slope = slope(reading, math, count);
    double b_intercept = intercept(reading, math, count);
    for(int j = 0; j < count; j++){
        math_predicted[j] = b_intercept + b_slope * reading[j];
    }
    printf("MAE  (Mean Absolute Error):       %.4f\n", mae(math, math_predicted, count));
    printf("RMSE (Root Mean Square Error):    %.4f\n", rmse(math, math_predicted, count));
    printf("MAPE (Mean Abs Percentage Error): %.4f%%\n", mape(math, math_predicted, count));
 
// --- POINT ESTIMATE AND CONFIDENCE INTERVALS ---
// "we estimate the true avg math score of ALL students is around"
    printf("\n--- CONFIDENCE INTERVALS FOR MATH SCORE ---\n");
    printf("Point Estimate (sample mean): %.4f\n", point_estimate(math, count));
    confidence_interval(math, count, 1.645);   // 90%
    confidence_interval(math, count, 1.96);    // 95%
    confidence_interval(math, count, 2.576);   // 99%
 
// --- PREP COURSE ANALYSIS ---
// does test prep course actually help? 
    printf("\n--- PREP COURSE: DOES IT ACTUALLY HELP? ---\n");
    double prep_scores[MAX_ROWS], noprep_scores[MAX_ROWS];
    int prep_cnt = 0, noprep_cnt = 0;
 
    for(int j = 0; j < count; j++){
        if(strcmp(prep_course[j], "completed") == 0){
            prep_scores[prep_cnt++] = total_pct[j];
        } else {
            noprep_scores[noprep_cnt++] = total_pct[j];
        }
    }
 
    double prep_avg   = mean(prep_scores,   prep_cnt);
    double noprep_avg = mean(noprep_scores, noprep_cnt);
    printf("Avg score WITH prep course:    %.2f\n", prep_avg);
    printf("Avg score WITHOUT prep course: %.2f\n", noprep_avg);
    printf("Std Dev WITH prep:    %.2f\n", std_dev(prep_scores, prep_cnt));
    printf("Std Dev WITHOUT prep: %.2f\n", std_dev(noprep_scores, noprep_cnt));
    printf("Verdict: Prep course %s.\n", (prep_avg > noprep_avg ? "HELPS (go study bhai)" : "does NOT help lol"));
 
// quartile of total_pct - to see overall class distribution
    printf("\n--- OVERALL CLASS SCORE QUARTILES ---\n");
    QuartileResult qtotal = Quartile(total_pct, count);
 
// confidence interval for total score
    printf("\n--- CONFIDENCE INTERVAL FOR TOTAL SCORE ---\n");
    confidence_interval(total_pct, count, 1.96);
 
// --- LUNCH TYPE ANALYSIS ---
// standard vs free/reduced lunch - does being poor affect marks? sad but real
    printf("\n--- LUNCH TYPE vs MARKS ---\n");
    double std_lunch[MAX_ROWS], red_lunch[MAX_ROWS];
    int sl_cnt = 0, rl_cnt = 0;
 
    for(int j = 0; j < count; j++){
        if(strcmp(lunch[j], "standard") == 0){
            std_lunch[sl_cnt++] = total_pct[j];
        } else {
            red_lunch[rl_cnt++] = total_pct[j];
        }
    }
    printf("Avg score (standard lunch):      %.2f\n", mean(std_lunch, sl_cnt));
    printf("Avg score (free/reduced lunch):  %.2f\n", mean(red_lunch, rl_cnt));
    printf("Median (standard):    %.2f\n", median(std_lunch, sl_cnt));
    printf("Median (free/reduced):%.2f\n", median(red_lunch, rl_cnt));
    // convert lunch to 0/1 for correlation
    double lunch_num[MAX_ROWS];
    for(int j = 0; j < count; j++){
        lunch_num[j] = (strcmp(lunch[j], "standard") == 0) ? 1.0 : 0.0;
    }
    printf("Correlation (lunch type vs total score): ");
    corr(lunch_num, total_pct, count);
 
// --- FINAL PREDICTION GAME ---
// ok this is the fun part
// given edu_rank and prep, can we predict total score roughly?
// using edu_rank -> total_pct regression
    printf("\n--- PREDICTION GAME ---\n");
    printf("(Using parent edu rank to predict student total score)\n");
 
    double edu_slope     = slope(edu_rank, total_pct, count);
    double edu_intercept = intercept(edu_rank, total_pct, count);
    printf("Equation: predicted_score = %.2f + %.2f * edu_rank\n", edu_intercept, edu_slope);
 
    // predict for each level
    printf("Predicted score if parent = some high school (rank 1): %.2f\n", predict_y(1.0, edu_rank, total_pct, count));
    printf("Predicted score if parent = high school      (rank 2): %.2f\n", predict_y(2.0, edu_rank, total_pct, count));
    printf("Predicted score if parent = some college     (rank 3): %.2f\n", predict_y(3.0, edu_rank, total_pct, count));
    printf("Predicted score if parent = associate degree (rank 4): %.2f\n", predict_y(4.0, edu_rank, total_pct, count));
    printf("Predicted score if parent = bachelor degree  (rank 5): %.2f\n", predict_y(5.0, edu_rank, total_pct, count));
    printf("Predicted score if parent = master degree    (rank 6): %.2f\n", predict_y(6.0, edu_rank, total_pct, count));
 
    // reverse: if i got 80, what edu rank does my parent probably have?
    double mystery_score = 80.0;
    double guessed_rank = predict_x(mystery_score, edu_rank, total_pct, count);
    printf("\nIf a student scores %.0f, parent probably has edu rank: %.2f\n", mystery_score, guessed_rank);
    // lets round it and tell what level
    int r_rank = (int)(guessed_rank + 0.5);
    if(r_rank <= 1)      printf("= some high school level parent\n");
    else if(r_rank == 2) printf("= high school level parent\n");
    else if(r_rank == 3) printf("= some college level parent\n");
    else if(r_rank == 4) printf("= associate degree parent\n");
    else if(r_rank == 5) printf("= bachelor degree parent\n");
    else                 printf("= master degree parent\n");
 
 
    return 0;
    
}