double lagrange4(const double *x, const float *y, double x0) {
    double d00 = x[0] - x[1];
    double d01 = x[0] - x[2];
    double d02 = x[0] - x[3];
    
    double d10 = x[1] - x[0];
    double d11 = x[1] - x[2];
    double d12 = x[1] - x[3];
    
    double d20 = x[2] - x[0];
    double d21 = x[2] - x[1];
    double d22 = x[2] - x[3];
    
    double d30 = x[3] - x[0];
    double d31 = x[3] - x[1];
    double d32 = x[3] - x[2];

    double result = 0.0;

    // Term 0
    result += (double)y[0] * (x0 - x[1]) * (x0 - x[2]) * (x0 - x[3]) / (d00 * d01 * d02);

    // Term 1
    result += (double)y[1] * (x0 - x[0]) * (x0 - x[2]) * (x0 - x[3]) / (d10 * d11 * d12);

    // Term 2
    result += (double)y[2] * (x0 - x[0]) * (x0 - x[1]) * (x0 - x[3]) / (d20 * d21 * d22);

    // Term 3
    result += (double)y[3] * (x0 - x[0]) * (x0 - x[1]) * (x0 - x[2]) / (d30 * d31 * d32);

    return result;
}