#include "stat.h"
#include <stdio.h>

void sort(double arr[], int size)
{
    for(int i = 0; i < size - 1; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            if(arr[i] > arr[j])
            {
                double temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

double sqrt_val(double x)
{
    if(x <= 0)
        return 0;

    double guess = x;
    double epsilon = 0.000001; 

    while(1)
    {
        double next = 0.5 * (guess + x / guess);

        if((next - guess < epsilon) && (guess - next < epsilon))
            break;

        guess = next;
    }

    return guess;
}

double abs_val(double x)
{ 
    if(x<0)
        return -x;
    return x;
}

double mean(double arr[], int size)
{
    if(size <= 0) return 0;
    double value = 0;
    for(int i = 0; i<size; i++ ){
        value = value + arr[i];
    }
    return value/size;
}

double median(double arr2[], int size){
    if(size <= 0) return 0;
    double arr[size];
    for(int i = 0;i<size;i++)
    arr[i] = arr2[i];
    sort(arr,size);
    
    if(size%2==0){
        double c =(arr[size/2] + arr[(size/2)-1])/2.0;
        return c;}
    else{
        double c = arr[(size)/2];
        return c;
    }
}

double mode(double arr[], int size){
    if(size <= 0) return 0;
    int maxcount = 0;
    double Final_value = arr[0];
    for(int i = 0; i<size; i++){
        int count = 0;
        for(int j = 0; j<size; j++){
            if(arr[i] == arr[j]){
                ++count;
            }}
        
        if(count >maxcount){
           maxcount = count;
           Final_value = arr[i];
        }}
    return Final_value;
    }

double range(double arr[],int size){
    if(size <= 0) return 0;
    double max= arr[0], min = arr[0];

    for(int i = 0; i<size;i++){
        if (arr[i]>max){
            max = arr[i];
        }
        if(arr[i]<min){
            min = arr[i];
        }
    }
    return max-min;

}


double mean_deviation(double arr[], int size, int med_mean){
    if(size <= 0) return 0;
    double m = mean(arr, size);
    double med = median(arr, size);
    double sum_mean = 0;
    double sum_median = 0;
    for(int i = 0; i<size; i++){
        sum_mean = abs_val(arr[i] - m) + sum_mean;

        sum_median = abs_val(arr[i] - med) + sum_median;

    }
    printf("Mean: %f, Median: %f",(sum_mean/(size)), (sum_median/(size)));
    if (med_mean == 1) return sum_mean/size;
    else return sum_median/size;
}



double var(double arr[], int size){
    if(size < 2) return 0;
    double m = mean(arr, size);
    double sum_mean = 0;
    for(int i = 0; i<size; i++){
        sum_mean = (((arr[i] - m)*(arr[i] - m)) + sum_mean);
        }

        return (sum_mean/(size-1));
}

double std_dev(double arr[], int size){
    if(size <2) return 0;
    return sqrt_val(var(arr, size));
}

double skewnesscoeff(double arr[], int size, int useMedian)
{
    double m = mean(arr, size);
    double sd = std_dev(arr, size);

    if(sd == 0) return 0;

    if(useMedian)
    {
        double med = median(arr, size);
        return (3 * (m - med)) / sd;
    }
    else
    {
        double mod = mode(arr, size);
        return (m - mod) / sd;
    }
}

double moment(double arr[], int size, int order){
    double m = mean(arr,size);
    double sum = 0;
    for(int i = 0; i< size; i++){
        double product = 1;
        for (int j =0; j < order ; j++){
        product = (arr[i]-m) * product;}
        sum = product + sum;
    }

    return sum/size;
}

double skewness(double arr[], int size){
    double m2 = moment(arr, size, 2);
    if(m2 == 0) return 0;                          
    double sk = moment(arr,size,3) / sqrt_val(m2*m2*m2);
    if(sk < 0)       printf("left skew\n");
    else if(sk == 0) printf("Symmetric skew\n");
    else             printf("right skew\n");
    return sk;
}
double kurtosis(double arr[], int size){
    double m2 = moment(arr, size, 2);
    if(m2 == 0) return 0;                          
    double b = moment(arr,size,4) / (m2*m2);
    if(b < 3)       printf("platykurtic\n");
    else if(b == 3) printf("mesokurtic\n");
    else            printf("leptokurtic\n");
    return b;
}

double kur_coeff(double arr[],int size){
    return (kurtosis(arr,size) - 3);
}

QuartileResult Quartile(double arr2[], int size) {
    QuartileResult r;

    double arr[size];
    for(int i = 0; i < size; i++)
        arr[i] = arr2[i];
    sort(arr, size);

    double Q1, Q2, Q3;
    double templ[size/2], tempu[size/2];

    if(size % 2 == 0) {
        for(int i = 0; i < size/2; i++)
            templ[i] = arr[i];
        for(int i = size/2; i < size; i++)
            tempu[i - size/2] = arr[i];
    } else {
        for(int i = 0; i < size/2; i++)
            templ[i] = arr[i];
        for(int i = size/2+1; i < size; i++)
            tempu[i - (size/2+1)] = arr[i];
    }

    Q1 = median(templ, size/2);
    Q2 = median(arr, size);
    Q3 = median(tempu, size/2);

    r.Q1  = Q1;
    r.Q2  = Q2;
    r.Q3  = Q3;
    r.IQR = Q3 - Q1;
    r.QD  = r.IQR / 2.0;

    printf("\nQ1: %f, Q2: %f, Q3: %f, IQR: %f, QD: %f\n",
            r.Q1, r.Q2, r.Q3, r.IQR, r.QD);

    return r;
}

double cov(double arr1[], double arr2[], int size){
    double r = 0;
    double m1 = mean(arr1,size);
    double m2 = mean(arr2,size);

    for(int i = 0; i<size;i++){
        r = (arr1[i]-m1)*(arr2[i]-m2) + r;
    }
    return r/size;
}
double corr(double arr1[], double arr2[], int size){
    if(var(arr1,size) == 0 || var(arr2,size) == 0) return 0;  

    double r = cov(arr1,arr2,size) / sqrt_val(var(arr1,size)*var(arr2,size));

    if(r == 1){
        printf("Perfect Positive Correlation: %f\n", r);
    }
    else if(r == -1){
        printf("Perfect Negative Correlation: %f\n", r);
    }
    else if(r == 0){
        printf("No Correlation: %f\n", r);
    }
    else if(r > 0 && r <= 0.25){
        printf("Weak Positive Correlation: %f\n", r);
    }
    else if(r > 0.25 && r < 0.75){
        printf("Moderate Positive Correlation: %f\n", r);}
    else if(r >= 0.75 && r < 1){
        printf("Strong Positive Correlation: %f\n", r);
    }
    else if(r < 0 && r >= -0.25){
        printf("Weak Negative Correlation: %f\n", r);
    }
    else if(r < -0.25 && r > -0.75){
        printf("Moderate Negative Correlation: %f\n", r);
    }
    else if(r <= -0.75 && r > -1){
        printf("Strong Negative Correlation: %f\n", r);
    }

    return r;
}

double slope(double arr1[], double arr2[], int size){
    if(var(arr1,size) == 0 || var(arr2,size) == 0) return 0; 
    return cov(arr1, arr2, size) / var(arr1, size);
}

double intercept(double arr1[], double arr2[], int size){
    return mean(arr2, size) - slope(arr1, arr2, size) * mean(arr1, size);
}

double r_squared(double arr1[], double arr2[], int size){
    double r = corr(arr1, arr2, size);
    return r * r;
}
double slope_xony(double x[], double y[], int size) {
    if(var(y, size) == 0) return 0;       
    return cov(x, y, size) / var(y, size);
}
double predict_x(double y_val, double x[], double y[], int size) {
    double bxy = slope_xony(x, y, size);
    return mean(x, size) + bxy * (y_val - mean(y, size));
}

int three_sigma(double arr[],int size){
    double m = mean(arr,size);
    double l_b = m - (3*std_dev(arr,size));
    double u_b = m + (3*std_dev(arr,size));
    double outlier[size];
    int count = 0;
    for (int i = 0; i<size; i++){
        if (arr[i] < l_b || arr[i] > u_b){
            outlier[count] = arr[i];
            count++;
        
        }
    }
    for( int i = 0; i < count; i++)
    printf("Outlier: %f\n", outlier[i]);

    if(count == 0) return 0;
    else return 1;
}

double Mad(double arr[], int size){
    double m = median(arr,size);
    double m1[size];
    for(int i = 0; i<size; i++){
        m1[i]= abs_val(arr[i]-m);
    }
    return median(m1,size);
}

int mad_outlier(double value, double arr[], int size) {
    double med = median(arr, size);
    double mad = Mad(arr, size);
    if(abs_val(value - med) > 2.5 * mad) return 1;
    return 0;
}

int boxplot_bound(double arr[], int size){
    QuartileResult r = Quartile(arr,size);
    double l_b = r.Q1 - 1.5 * r.IQR;
    double u_b  = r.Q3 + 1.5*r.IQR;
    double outlier[size];
    int count = 0;
    for (int i = 0; i<size; i++){
        if (arr[i] < l_b || arr[i] > u_b){
            outlier[count] = arr[i];
            count++;
        
        }
    }
    for( int i = 0; i < count; i++)
    printf("Outlier: %f\n", outlier[i]);

    if(count == 0) return 0;
    else return 1;
    
}

double mae(double actual[], double predicted[], int size) {
    double m = 0;
    for (int i = 0; i<size;i++){
        m = abs_val((actual[i] - predicted[i])) + m ;
    }

    return m/size;
}

double rmse(double actual[], double predicted[], int size) {
    double m = 0;
    for (int i = 0; i<size;i++){
        m = ((actual[i] - predicted[i])*(actual[i] - predicted[i])) + m ;
    }

    return sqrt_val(m/size);
}

double mape(double actual[], double predicted[], int size) {
    double m = 0;
    int valid = 0;                                       
    for(int i = 0; i < size; i++) {
        if(actual[i] == 0) continue;
        m += abs_val((actual[i] - predicted[i]) / actual[i]);
        valid++;                                         
    }
    if(valid == 0) return 0;                           
    return (m / valid) * 100;                           
}

double predict_y(double x_val, double x[], double y[], int size) {
    double byx = slope(x, y, size);
    return mean(y, size) + byx * (x_val - mean(x, size));
}

double point_estimate(double arr[], int size) {
    return mean(arr, size);
}

void confidence_interval(double arr[], int size, double z){
    if(size <= 0 || z <= 0) return;       
    double std_error = std_dev(arr, size) / sqrt_val((double)size); 
    double margin    = z * std_error;
    double m         = mean(arr, size);

    double lower = m - margin;
    double upper = m + margin;

    if(abs_val(z - 1.645) < 0.0001)      printf("90%% Confidence Interval:\n");
    else if(abs_val(z - 1.96) < 0.0001)  printf("95%% Confidence Interval:\n");
    else if(abs_val(z - 2.576) < 0.0001) printf("99%% Confidence Interval:\n");
    else printf("Confidence Interval (z = %f):\n", z);

    printf("Lower: %f\n", lower);
    printf("Upper: %f\n", upper);
}
