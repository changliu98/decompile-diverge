int condF(int a, float *b, int c, float *d, int e, float *f, float *g, float *h, float *i) {
    if (a == c && a == e && a == g && a == i) {
        for (int j = 0; j < a; j++) {
            float tmp;
            if (d[j] > b[j]) {
                tmp = f[j];
            } else {
                if (b[j] > d[j]) {
                    tmp = h[j];
                } else {
                    tmp = g[j];
                }
            }
            i[j] = tmp;
        }
        return 0;
    } else {
        return 2000;
    }
}