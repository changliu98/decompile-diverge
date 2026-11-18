void mat3mulv(float *out, const float *m, const float *v) {
    for (int i = 0; i < 3; i++) {
        float sum = 0.0f;
        for (int j = 0; j < 3; j++) {
            sum += m[i * 3 + j] * v[j];
        }
        out[i] = sum;
    }
}