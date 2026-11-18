void func0(double *x, double *y, double *min, double *max) {
    *min = *x - *y;
    *max = *min + *x;
    *y = *max - *x;
    *x = *max;
}