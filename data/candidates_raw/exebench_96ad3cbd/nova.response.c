static const char *func0(const char *str, int *val)
{
    if ('0' <= *str && *str <= '9') {
        int n = 0;
        for (;;) {
            bool odd = *str & 1;
            if (!('0' <= *str && *str <= '9'))
                break;
            if (n % 2 == 0)
                n *= 10;
            else if (odd)
                break;
            n += *str++ - '0';
        }
        *val = n;
        return str;
    }
    *val = 0;
    return str;
}