#ifndef STAT_H  
#define STAT_H

typedef struct {
    double Q1;
    double Q2;
    double Q3;
    double IQR;
    double QD;
} QuartileResult;


void   sort       (double arr[], int size);
double sqrt_val   (double x);
double abs_val    (double x);


double mean           (double arr[], int size);
double median         (double arr[], int size);
double mode           (double arr[], int size);
double range          (double arr[], int size);
double mean_deviation (double arr[], int size, int med_mean);
double var            (double arr[], int size);
double std_dev            (double arr[], int size);
double moment         (double arr[], int size, int order);
double skewnesscoeff  (double arr[], int size, int useMedian);
double skewness       (double arr[], int size);
double kurtosis       (double arr[], int size);
double kur_coeff      (double arr[], int size);
QuartileResult Quartile(double arr[], int size);
double cov        (double x[], double y[], int size);
double corr       (double x[], double y[], int size);
double slope      (double x[], double y[], int size);
double slope_xony (double x[], double y[], int size);
double intercept  (double x[], double y[], int size);
double r_squared  (double x[], double y[], int size);
double predict_y  (double x_val, double x[], double y[], int size);
double predict_x  (double y_val, double x[], double y[], int size);
int    three_sigma   (double arr[], int size);
double Mad           (double arr[], int size);
int    mad_outlier   (double value, double arr[], int size);
int    boxplot_bound (double arr[], int size);
double mae           (double actual[], double predicted[], int size);
double rmse          (double actual[], double predicted[], int size);
double mape          (double actual[], double predicted[], int size);
double point_estimate       (double arr[], int size);
void   confidence_interval  (double arr[], int size, double z);


#endif 