int ellipsis(char *str, int len)
{
    int i, j, k, e = 0;
    char *p;

    if (str == NULL || len < 0)
        return 0;

    if (len < 3) {
        str[len] = '\0';
        return 1;
    }

    p = str;
    i = len - 3;
    while (*p && i--) {
        if (e)
            e = 0;
        else if (*p & 0x80)
            e = 1;
        p++;
    }

    p = str;
    i = 3;
    while (*p && i--)
        p++;

    if (*p && i == 0) {
        str[len] = '\0';
        *p++ = '.';
        *p++ = '.';
        if (!e && (*p & 0x80))
            *p = '.';
    }

    return 1;
}