void str_replace(char *str, char old, char new)
{
    if (str)
        for (str = (char *)str; *str; str++)
            if (*str == old)
                *str = new;
}