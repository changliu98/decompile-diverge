char *mystpcpy(char *dest, const char *src)
{
    while ((*dest = *src) != '\0') {
        src++;
        dest++;
    }
    return dest;
}