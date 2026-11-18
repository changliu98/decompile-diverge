char *strcpy(char *dest, const char *src)
{
    char *dest_local;
    const char *src_local;

    src_local = src;
    dest_local = dest;

    while (*src_local != '\0') {
        *dest_local = *src_local;
        dest_local++;
        src_local++;
    }

    *dest_local = '\0';

    return dest;
}