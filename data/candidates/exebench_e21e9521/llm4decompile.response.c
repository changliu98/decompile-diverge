float avg12(float *x, float *y, size_t n)
{
    float sum = 0;
    for (size_t i = 0; i < n; i++)
        sum += x[i] * x[i] * y[i];
    return sum / n;
}