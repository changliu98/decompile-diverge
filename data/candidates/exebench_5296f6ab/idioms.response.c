void charset_remove(char *str, char c)
{
    char *src = str;
    char *dst = str;
    while (*src != '\0') {
        if (*src == c)
            ++src;
        else
            *dst++ = *src++;
    }
    *dst = '\0';
}