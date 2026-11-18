int fit_line(const double *x, const double *y, int n, double *slope, double *intercept) {
    double sum_x2 = 0.0;
    double sum_xy = 0.0;
    double sum_y = 0.0;
    double sum_x = 0.0;

    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_x2 += x[i] * x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
    }

    double denominator = (double)n * sum_x2 - sum_x * sum_x;
    
    if (denominator == 0.0) {
        return -1;
    }

    *slope = (sum_y * sum_x2 - sum_x * sum_xy) / denominator;
    *intercept = ((double)n * sum_xy - sum_x * sum_y) / denominator;

    return 0;
}