int *func0(int n, int *size)
{
    int *factors = (int*)malloc(sizeof(int)*100);
    int i = 0;
    *size = i;
    for(int i = 2; i*i <= n; i++)
    {
        while(n % i == 0)
        {
            n = n / i;
            factors[(*size)++] = i;
        }
    }
    if(n > 1)
    {
        factors[(*size)++] = n;
    }
    return factors;
}