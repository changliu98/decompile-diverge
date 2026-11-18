void quad_2_grad(double *out, const double *a, const double *x, const double *y) {
    // out[0] = a[0] + x[0] * y[0] + x[1] * y[1]
    out[0] = a[0] + x[0] * y[0] + x[1] * y[1];
    
    // out[1] = a[1] + x[1] * y[0] + x[2] * y[1]
    out[1] = a[1] + x[1] * y[0] + x[2] * y[1];
}