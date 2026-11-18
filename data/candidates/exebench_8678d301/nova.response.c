float vec_dot_prodf(float *v1, float *v2, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += v1[i] * v2[i];
    }
    return sum;
}