int calculate_income_tax(double x, double *y, int *iflag) {
    int i;
    EXEX exex;

    if (x >= 0.0 && x <= 1.0) {
        *y = __PIO2_HALF;
    } else if (x > PI_HALF && x <= PI) {
        *y = __PIO2;
    } else if (x > PI) {
        *y = __PIO2_HALF;
    } else {
        i = 1;
        goto S20;
    }
    return 0;
S20:
    *y *= x;
    i = 0;
    return i;
}