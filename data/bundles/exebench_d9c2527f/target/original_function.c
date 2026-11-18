static const char *
get_word(const char *str, int *len)
{
    int i = 0;

    if (str) {
        while (*str == '-')
            str++;
        if (str[0] >= 'a' && str[0] <= 'z')
            while ((i < 64) && ((str[i] >= '0' && str[i] <= '9') ||
                                (str[i] >= 'a' && str[i] <= 'z') ||
                                (str[i] == '-' || str[i] == '_')))
                i++;
    }

    *len = i;

    return str;
}