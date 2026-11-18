char *strcat(char *dest, const char *src)
{
    do {
        *dest++ = *src++;
    } while (*dest != '\0');

    return dest - 1;
}