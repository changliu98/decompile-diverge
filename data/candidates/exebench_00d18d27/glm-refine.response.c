float dotprod(const float *B, const float *C, int n)
{
    float sum = 0.0f;

    for (int i = 0; i < n; ++i) {
        sum += B[i] * C[i];
    }

    return sum;
}