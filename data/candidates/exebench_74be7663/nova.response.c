void mlPointSub(float *a, float *b) {
    for (int i = 0; i < 4; i++)
        a[i] -= b[i];
}