static int func0(double x, double *r) {
    int q;

    if (x < -1.0) {
        q = 1;
        *r = x;
    } else if (x <= MAX_LOG) {
        q = 0;
        *r = x;
    } else {
        q = (int)x;
        *r = x - (double)q;
    }
    return q;
}