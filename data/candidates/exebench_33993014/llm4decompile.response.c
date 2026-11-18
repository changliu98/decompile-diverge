int LI_ltostr(char *str, long val)
{
    char *p, *q, *end, *swap;
    int len;

    p = q = str;
    len = 1;
    if (val < 0) {
        *p++ = '-';
        len++;
        val = -val;
    }
    end = p;
    while (val >= 10) {
        *end++ = (val % 10) + '0';
        val /= 10;
    }
    *end++ = val + '0';
    *end = '\0';
    len += end - p;
    while (p < end--) {
        swap = *end;
        *end = *p;
        *p++ = swap;
    }
    return len;
}