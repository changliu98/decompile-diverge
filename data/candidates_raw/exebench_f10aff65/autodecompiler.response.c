float dot(float *v, float *u, int n)
{
    int i;
    float sum = 0.0;

    for (i = 0; i < n; i++)
        sum += v[i] * u[i];

    return sum;
}