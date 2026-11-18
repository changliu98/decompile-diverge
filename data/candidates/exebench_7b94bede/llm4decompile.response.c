void
mlMatrixTransposeTo(
    const float *a,
    float *result)
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            result[i * 4 + j] = a[j * 4 + i];
        }
    }
}