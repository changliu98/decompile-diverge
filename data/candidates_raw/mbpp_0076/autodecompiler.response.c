int binom(int k, int n)
{
    if(n < k)
    {
        int tmp = k;
        k = n;
        n = tmp;
    }
    int a = k * (k + 1) * (2 * k + 1) / 6 + (n - k) * k * (k + 1) / 2;

    return a;
}