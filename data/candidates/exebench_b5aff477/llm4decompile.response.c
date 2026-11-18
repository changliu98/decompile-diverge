float dotprod(float *v1, float *v2, int len)
{
    int i;
    float dot;

    dot = 0;
    for (i = 0; i < len; i++)
        dot += v1[i] * v2[i];

    return dot;
}