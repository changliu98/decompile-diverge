void rgb2cmyk(double *x, double *y, double *z, double *max, double *min) {
    *max = 1.0 - *x;
    *y = 1.0 - *y;
    *z = 1.0 - *z;

    if (*max < *y)
        *max = *y;
    else
        *max = *max;

    if (*max < *z)
        *max = *z;
    else
        *max = *max;

    *min = *max - *x;
    *y = *min - *y;
    *z = *min - *z;
}