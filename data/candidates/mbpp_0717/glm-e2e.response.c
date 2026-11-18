double func0(double *arr, int n) {
    double result = 0.0;
    
    if (n > 1) {
        double mean = avg_calc(arr, n);
        double sum_sq_diff = 0.0;
        
        for (int i = 0; i < n; i++) {
            double diff = arr[i] - mean;
            sum_sq_diff += diff * diff;
        }
        
        sum_sq_diff = sqrt(sum_sq_diff / (n - 1));
        result = sum_sq_diff;
    }
    
    return result;
}