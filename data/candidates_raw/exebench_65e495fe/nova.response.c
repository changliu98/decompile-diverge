static size_t func0(unsigned char *s, size_t *len, unsigned char c)
{
    if (*len < sizeof(c))
        return 0;
    *s++ = c;
    *len = *len + 1;
    return 1;
}