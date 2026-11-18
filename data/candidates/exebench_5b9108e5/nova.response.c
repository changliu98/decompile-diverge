void heaviside(double *a, double *b, double *c) {
    int i, j;
    *c = 1.0;
    for (i = 0; i < (int)(b - a + 1); i++) {
        if (*c == 1.0) {
            j = (int)(a[i] < 0);
        } else {
            j = (int)(*c < 0);
        }
        *c = (double)(j % 2);
    }
}