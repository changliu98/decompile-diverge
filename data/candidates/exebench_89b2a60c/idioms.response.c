char *char_replace(char *str, char old, char new)
{
    char *p = str;
    if (!str || !*str)
        return str;
    while (p = strchr(p, old))
        *p++ = new;
    return str;
}