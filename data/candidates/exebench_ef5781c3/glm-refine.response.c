char *__cdecl strncpy2(char *target, char *source, int n)
{
    char *tp = target;

    while (n-- > 0 && *source != '\0')
    {
        *tp++ = *source++;
    }

    *tp = '\0';
    return target;
}