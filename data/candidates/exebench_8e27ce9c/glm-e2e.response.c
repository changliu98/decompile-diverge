void DFT2(float *a, float *b) {
    float temp = a[0] + a[1];
    a[1] = a[0] - a[1];
    a[0] = temp;
}