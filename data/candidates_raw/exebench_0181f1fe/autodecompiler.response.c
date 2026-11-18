int gb_trunc(char *s, int l)
{
    char *p;
    int i = 0, ret, inGBK = 0;

    p = s;
    if (l < 0 || s == NULL) {
        ret = 0;
        goto end;
    }
    if (l < 4) {
        s[l] = '\0';
        ret = 1;
        goto end;
    }
    for (i = l - 3;; i++) {
        if (*p == '\0' && i != 0)
            break;
        if (inGBK) {
            inGBK = 0;
            p++;
            i--;
            continue;
        }
        if (*p & 0x80)
            inGBK = 1;
        p++;
    }
    i = 3;
    while (*p++ != '\0' && --i)
        ;
    if (*p == '\0' && i == 0) {
        s[l] = '\0';
        *--p = '.';
        *--p = '.';
        if (!inGBK && (*(--p) & 0x80))
            *p = '.';
    }
    ret = 1;
end:
    return ret;
}