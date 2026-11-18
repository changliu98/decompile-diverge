void func0(long n, long *p, long *q) {
    long i;

    if (n <= 0)
        return;

    func0(n / 2, p, q);

    for (i = 1; i <= n; i++)
        *p += *q;
}