#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stat.h"

#define MAX 1000

int main(){
    FILE *fp = fopen("sensor_clean.csv", "r");
    if(fp == NULL){
        printf("file not found\n");
        return 1;
    }

    char line[512];
    int count = 0;

    double engagement[MAX], attention[MAX], feedback[MAX];
    double noise[MAX], temp[MAX], learning[MAX];

    fgets(line, sizeof(line), fp);

    while(fgets(line, sizeof(line), fp)){
        char *token = strtok(line, ",");
        int col = 0;

        while(token != NULL){
            if(col == 1) engagement[count] = atof(token);
            if(col == 2) attention[count] = atof(token);
            if(col == 3) feedback[count] = atof(token);
            if(col == 4) noise[count] = atof(token);
            if(col == 5) temp[count] = atof(token);
            if(col == 6) learning[count] = atof(token);

            token = strtok(NULL, ",");
            col++;
        }
        count++;
    }
    fclose(fp);

    printf("rows: %d\n\n", count);

    printf("mean: %.2f\n", mean(learning, count));
    printf("median: %.2f\n", median(learning, count));
    printf("mode: %.2f\n", mode(learning, count));
    printf("range: %.2f\n", range(learning, count));

    printf("mean deviation: %.2f\n", mean_deviation(learning, count, 1));
    printf("variance: %.2f\n", var(learning, count));
    printf("std dev: %.2f\n\n", std_dev(learning, count));

    printf("skew coeff: %.4f\n", skewnesscoeff(learning, count, 1));
    printf("skewness: %.4f\n", skewness(learning, count));
    printf("kurtosis: %.4f\n", kurtosis(learning, count));
    printf("excess kurtosis: %.4f\n\n", kur_coeff(learning, count));




    printf("quartiles:\n");
    Quartile(learning, count);

    printf("\nrelations:\n");
    double r1 = corr(engagement, learning, count);
    double r2 = corr(attention, learning, count);
    double r3 = corr(noise, attention, count);

    printf("\nobs:\n");
    if(r1 > 0.5) printf("engagement helps learning\n");
    if(r2 > 0.5) printf("attention matters\n");
    if(r3 < 0) printf("noise reduces attention\n");

    double m = slope(engagement, learning, count);
    double b = intercept(engagement, learning, count);

    printf("\nmodel m=%.3f b=%.3f\n", m, b);
    printf("r^2: %.4f\n", r_squared(engagement, learning, count));

    printf("predict y (x=80): %.2f\n", predict_y(80, engagement, learning, count));
    printf("predict x (y=80): %.2f\n", predict_x(80, engagement, learning, count));

    printf("\noutliers:\n");

    printf("3 sigma:\n");
    if(three_sigma(learning, count) == 0) printf("none\n");

    printf("MAD: %.4f\n", Mad(learning, count));

    printf("MAD outliers:\n");
    for(int i=0;i<count;i++){
        if(mad_outlier(learning[i], learning, count))
            printf("at %d\n", i);
    }

    printf("boxplot:\n");
    boxplot_bound(learning, count);

    double pred[MAX];
    for(int i=0;i<count;i++){
        pred[i] = m * engagement[i] + b;
    }

    printf("\nerrors:\n");
    printf("mae: %.4f\n", mae(learning, pred, count));
    printf("rmse: %.4f\n", rmse(learning, pred, count));
    printf("mape: %.4f%%\n", mape(learning, pred, count));

    printf("\nestimate: %.2f\n", point_estimate(learning, count));

    printf("\nconfidence:\n");
    confidence_interval(learning, count, 1.96);

    return 0;
}