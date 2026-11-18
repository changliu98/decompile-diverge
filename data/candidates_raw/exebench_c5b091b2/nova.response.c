int func0(double a, double b, double c, double *x) {
    int flag;
    if ((a - c) * (b - c) > 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    *x = (b - a) / (c - a);
    return flag;
}