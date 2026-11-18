void strrev(char *str)
{
    unsigned long i; unsigned long j;
    unsigned long len = strlen(str);
    char tmp;
    if (len == 0)
        return;
    for (i = 0, j = len - 1; i < j; i++, j--)
    {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}