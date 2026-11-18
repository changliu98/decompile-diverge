void dot(float *a, float *b, float *result) {
    *result = 0.0f;
    for (int i = 0; i < 5; i++) {
        *result += a[i] * b[i];
    }
}