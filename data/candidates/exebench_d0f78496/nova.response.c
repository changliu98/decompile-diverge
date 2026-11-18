static const char *read_int(const char *s, int len, int *value)
{
    unsigned int ret = 0;
    do {
        if (len-- < 0 || *s < '0' || *s > '9') {
            *value = ret;
            return s;
        }
        ret = ret * 10 + (*s - '0');
    } while (*s++);
    *value = ret;
    return s;
}