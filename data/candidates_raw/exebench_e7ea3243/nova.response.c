void func0(float *mat, float s) {
    float mat_t[3][3];
    float s_t[3][3] = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}};
    float *p = &mat[0][0];
    float *q = &mat_t[0][0];
    float *r = &s_t[0][0];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            *q = *p * *r;
            q++;
            p++;
            r++;
        }
    }
    memcpy(&mat[0][0], &mat_t[0][0], sizeof(float) * 9);
}