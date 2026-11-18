static void func0(int n, int *x, int *y) {
    int i;
    if (n == 0) {
        for (i = 0; i < 7; i++)
            y[i] = (x[i] * 255) >> 8;
    } else {
        for (i = 0; i < 7; i++) {
            int v = x[i] * n;
            int s = (v < 0)? -128 : 128;
            y[i] = (x[i] * n) >> 8;
            y[i] += s;
        }
    }
    y[4] = x[4];
    y[5] = x[5];
    y[6] = x[6];
    y[7] = x[7];
    y[0] = n;
}