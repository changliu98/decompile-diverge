static _Bool is_prime(long n)
{
    if (n % 2 == 0)
        return 0;
    if (n == 1)
        return 1;
    long i = n + 1;
    long j = 0;
    while (i % 2 == 0) {
        i /= 2;
        j++;
        if (i == j)
            return 1;
    }
    return 0;
}