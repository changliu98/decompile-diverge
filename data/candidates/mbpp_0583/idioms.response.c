int func0(int n)
{
    if (n <= 1)
        return 1;
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        int a = func0(i);
        int b = func0(n - i - 1);
        res += a * b;
    }
    return res;
}