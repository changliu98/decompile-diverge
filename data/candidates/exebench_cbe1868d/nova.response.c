float vectorDotProduct(int n, float *px, float *py) {
    int i;
    float sum = 0;

    for (i = 0; i < n; i++) {
        sum += px[i] * py[i];
    }

    return sum;
}