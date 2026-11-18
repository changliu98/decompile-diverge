int dupfd(int n, int *p) {
    int r;
    if (n == -1) {
        *p = -1;
        r = 1;
    } else {
        *p = f(n);
        r = (*p!= -1) && (r);
    }
    return r;
}