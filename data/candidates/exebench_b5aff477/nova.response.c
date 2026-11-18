float dotprod(float *v1, float *v2, int n) {
    float result = 0;
    for (int i = 0; i < n; i++) {
        result += v1[i] * v2[i];
    }
    return result;
}