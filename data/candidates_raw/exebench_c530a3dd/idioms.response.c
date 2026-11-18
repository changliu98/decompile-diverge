int strlcpy(char *dst, char *src)
{
    int i = 0;
    char *dstp = dst;
    char *srcp = src;
    while (1) {
        if (*srcp == '\0')
            break;
        *dstp++ = *srcp++;
        if (*srcp == '\0')
            break;
        *dstp++ = *srcp++;
        if (*srcp == '\0')
            break;
        *dstp++ = *srcp++;
        if (*srcp == '\0')
            break;
        *dstp++ = *srcp++;
    }
    return i;
}