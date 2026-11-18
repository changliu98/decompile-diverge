int str_add_dot(char *str, int len)
{
    int i;
    int inGBK = 0;
    char *p = str;
    if (len < 0 || !str)
        return 0;
    if (len < 3) {
        str[len] = '\0';
        return 1;
    }
    for (i = len - 3; i > 0; i--) {
        int is_end = p[0] ? i : 0;
        if (is_end) {
            if (inGBK)
                inGBK = 0;
            else
                inGBK = p[0] & 0x80 ? 1 : 0;
            p++;
        } else
            break;
    }
    i = 3;
    do {
        int is_end = p[0] ? --i : 0;
    } while (is_end);
    if (p[0] && i == 0) {
        str[len] = '\0';
        p--;
        p[1] = '.';
        p--;
        p[1] = '.';
        if (!inGBK && p[-1] & 0x80)
            p--;
        p[1] = '.';
    }
    return 1;
}