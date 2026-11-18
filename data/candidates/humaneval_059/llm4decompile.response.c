int func0(int n)
{
    int i;

    for (i = 2; i * i <= n; i++) {
        for (; n % i == 0 && n > i; n /= i)
            ;
    }

    return n;
}