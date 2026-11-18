void strcpy_(char *s, char *t)
{
    while (*t != '\0')
        *s++ = *t++;
    *s = '\0';
}