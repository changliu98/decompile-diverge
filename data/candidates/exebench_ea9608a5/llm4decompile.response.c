void dec2bin(int n, char *rbn)
{
    int i;
    for (i = 0; n > 0; i++)
    {
        rbn[i] = n % 2 + '0';
        n /= 2;
    }
}