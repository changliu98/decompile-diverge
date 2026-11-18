void toUpperCase(char *s)
{
    while (*s)
    {
        if (*s >= 'a' && *s <= 'z')
            *s = *s + ('A' - 'a');
        s++;
    }
}