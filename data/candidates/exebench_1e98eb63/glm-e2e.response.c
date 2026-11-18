void getRange(double a, double b, double *min, double *max, double c) {
    if (b > c) {
        *max = c;
    } else {
        *max = b;
    }

    if (c > a) {
        *min = c;
    } else {
        *min = a;
    }
}