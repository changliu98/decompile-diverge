int is_empty(float *spectrum, int N)
{
    int i;
    for (i=0; i<=N; i++)
        if (spectrum[i] > 0.0001)
            return 0;
    return 1;
}