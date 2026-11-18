char *strcpy(char *dest, const char *src)
{
    char *tmp = dest;

    for (; *src != '\0'; src++) {
        *tmp++ = *src;
    }
    *tmp = '\0';

    return dest;
}