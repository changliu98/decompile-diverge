int func0(int n)
{
    int i, j, sum;
    unsigned char prime[n+1];

    for (i = 0; i <= n; i++)
        prime[i] = 1;

    for (i = 2; i*i <= n; i++)
        if (prime[i] & 1)
            for (j = i+i; j <= n; j += i)
                prime[j] = 0;

    sum = 0;
    for (i = 2; i <= n; i++)
        if (prime[i] & 1)
            sum += i;

    return sum;
}