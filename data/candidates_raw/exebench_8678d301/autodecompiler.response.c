float dot(float *v, float *u, int n)
{
    float sum = 0;
    int i;

    for (i = 0; i < n; i++)
        sum += v[i] * u[i];

    return sum;
}