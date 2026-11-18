int f(int n)
{
    if (n <= 1)
        return 1;
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        int a = f(i);
        int b = f(n - i - 1);
        res += a * b;
    }
    return res;
}