double Mat_doubleSwap(double *d) {
    char *c = (char *)d;
    char t;
    for (int i = 0; i < sizeof(double); i++) {
        t = c[i];
        c[i] = c[sizeof(double) - 1 - i];
        c[sizeof(double) - 1 - i] = t ^ c[i];
    }
    return *d;
}