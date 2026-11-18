int count(int n)
{
    int i, cnt = 0;
    for (i = 1; ; i *= 2)
    {
        if (i >= n + 2)
            break;
        if ((i & n) == 0)
            cnt++;
    }
    return cnt;
}