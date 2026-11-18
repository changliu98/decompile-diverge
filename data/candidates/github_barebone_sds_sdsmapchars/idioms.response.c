char *sdsmapchars(char *str, char *from, char *to, unsigned long setlen)
{
    unsigned long i; unsigned long j; unsigned long len = sdslen(str);
    for (i = 0; i < len; i++)
        for (j = 0; j < setlen; j++)
            if (str[i] == from[j])
            {
                str[i] = to[j];
                break;
            }
    return str;
}