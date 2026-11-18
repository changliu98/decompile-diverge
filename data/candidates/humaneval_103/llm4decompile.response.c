char* func0(int n, int m)
{
    if (n > m)
        return "-1";
    int num = (n + m) / 2;
    char* str = (char*)malloc(33);
    str[0] = '\0';
    str[32] = '\0';
    int i;
    for (i = 31; i >= 1; i--)
    {
        str[i] = num % 2 + '0';
        num /= 2;
        if (num == 0)
            break;
    }
    return str + i;
}