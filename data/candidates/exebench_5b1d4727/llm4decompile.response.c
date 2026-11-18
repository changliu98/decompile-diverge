float dotProduct(float *a, float *b, size_t size)
{
    int i;
    float sum = 0;
    for (i = 0; i < size; i++)
    {
        sum += a[i] * b[i];
    }
    return sum;
}