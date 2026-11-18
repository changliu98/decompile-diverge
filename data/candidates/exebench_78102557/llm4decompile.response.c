char *strcpy(char *dest, const char *src)
{
    char *tmp = dest;

    for (; (*tmp = *src) != '\0'; tmp++, src++)
        ;
    return dest;
}