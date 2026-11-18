int func0(int n)
{
    if (n < 0)
        return 0;
    if (n <= 1)
        return 1;
    return (int)(floor(log10(n / 2.718281828459045) * n + log10(2 * 3.141592653589793 * n) / 2)) + 1;
}