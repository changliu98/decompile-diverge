void _kahan_summation_step(double *x, double *y, double *min, double *max) {
    *min = *x - *y;
    *max = *min + *x;
    *y = *max - *x;
    *x = *max;
}