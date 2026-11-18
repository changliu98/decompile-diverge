float dotProduct(float *a, float *b, unsigned int n) {
    float result = 0.0f;
    for (unsigned int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }
    return result;
}