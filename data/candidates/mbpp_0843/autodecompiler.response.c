long func0(int n, int* primes, int primesSize)
{
    long* ugly = (long*)malloc(n*sizeof(long));
    int* indices = (int*)calloc(primesSize, sizeof(int));
    long* values = (long*)malloc(primesSize*sizeof(long));
    int i, j;
    long next_ugly;

    ugly[0] = 1;
    for(i = 0; i < primesSize; i++)
        values[i] = primes[i];
    i = 1;

    while(i < n)
    {
        next_ugly = values[0];
        for(j = 1; j < primesSize; j++)
            if(next_ugly > values[j])
                next_ugly = values[j];

        ugly[i] = next_ugly;

        for(j = 0; j < primesSize; j++)
            if(next_ugly == values[j])
                values[j] = primes[j]*ugly[++indices[j]];

        i++;
    }

    long ret = ugly[n-1];
    free(ugly);
    free(indices);
    free(values);

    return ret;
}