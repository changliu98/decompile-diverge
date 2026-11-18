void mat3mulv(float *dest, float *mat, float *v)
{
    int i, j;
    float r;
    for (i = 0; i < 3; i++) {
        r = 0.0f;
        for (j = 0; j < 3; j++) {
            r += mat[i * 3 + j] * v[j];
        }
        dest[i] = r;
    }
}