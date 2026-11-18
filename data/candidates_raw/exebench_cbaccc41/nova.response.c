int func0(double *x, double *y, double *min, double *max, double a,
                double b, double c, double d) {
    int flag = 0;
    if (*x > a) {
        *x = a;
        flag = 1;
    } else if (*x < b) {
        *x = b;
        flag = 1;
    }
    if (*y > c) {
        *y = c;
        flag = 1;
    } else if (*y < d) {
        *y = d;
        flag = 1;
    }
    return flag;
}