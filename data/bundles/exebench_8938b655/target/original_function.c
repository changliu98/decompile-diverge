int
itos(int i, char *s)
{
    int digit,j,k;
    char c;
    int ans;

    if (i < 0)
    {
        k = 0;
        i = -i;
        j = 1;
        s[0] = '-';
    }
    else
    {
        k = -1;
        j = 0;
    }

    do
    {
        digit = i % 10;
        i = i / 10;
        s[++k] = digit + '0';
    }
    while (i);

    s[k+1] = '\0';
    ans = k + 1;

    for (; j < k; ++j, --k)
    {
        c = s[j];
        s[j] = s[k];
        s[k] = c;
    }

    return ans;
}