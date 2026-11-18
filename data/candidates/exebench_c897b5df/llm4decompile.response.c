void
mlVectorScaleTo(
    const float *a,
    float b,
    float *result)
{
    int i;

    for (i = 0; i < 3; i++)
        result[i] = a[i] * b;
}