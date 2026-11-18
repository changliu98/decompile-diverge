int func0(int i, float *x, int n, float *fx, int k1, float *fk1, int k2,
              float *fk2) {
    int j, k;
    float f;

    if (i == n && i == k1 && i == k2) {
        f = 2000;
    } else {
        for (j = 0; j < i; j++) {
            if (x[j] > fx[i]) {
                f = fk1[j];
            } else if (x[j] < fx[i]) {
                f = fk2[j];
            } else {
                f = fx[j];
            }
            x[i] = f;
        }
        f = 0;
    }
    return f;
}