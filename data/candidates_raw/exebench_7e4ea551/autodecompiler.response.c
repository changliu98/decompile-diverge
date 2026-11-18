void strcpy(char *s, char *t)
{
    while (*t != '\0')
        *s++ = *t++;
    *s = *t;
}