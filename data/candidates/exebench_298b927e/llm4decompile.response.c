float FDot(float *v1, float *v2, int n)
{
    int i;
    float dot;

    dot = 0.0;
    for (i = 0; i < n; i++)
        dot += v1[i] * v2[i];

    return (dot);
}