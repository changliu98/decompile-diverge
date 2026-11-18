int func0(int n, int m)
{
    int result;
    if (m < 0)
        result = 0 - func0(n, 0 - m);
    else if (m == 0)
        result = 0;
    else if (m == 1)
        result = n;
    else
        result = n + func0(n, m - 1);
    return result;
}