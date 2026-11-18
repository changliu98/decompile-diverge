float func0(float *x, float *y, int n) {
    int i;
    float sum_x = 0, sum_y = 0;
    float sum_cross = 0;
    for (i = 0; i < n; i++) {
        sum_x += x[i] * y[i];
        sum_y += y[i] * y[i];
    }
    if (sum_x > 0)
        sum_cross = sum_x * sum_x / sum_y;
    else
        sum_cross = -sum_x * sum_x / sum_y;
    return sum_cross;
}