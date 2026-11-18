char *strcpy2(char *dest, char *src)
{
    int c;
    char *ret = dest;

    do {
        c = *dest++ = *src++;
    } while (c);

    return ret;
}