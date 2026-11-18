char *ft_strcpy(char *dest, const char *src)
{
    char *s = dest;
    for (;;)
    {
        if ((*s++ = *src++) == '\0')
        {
            return dest;
        }
    }
}