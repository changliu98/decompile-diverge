static const char *func0(const char *name, int *p_len)
{
    int len = 0;
    if (name)
    {
        while (name[len])
        {
            if (name[len] == '-')
                name = name + len + 1;
            else if (name[len] < 'a' || name[len] > 'z')
                break;
        }
    }
    while (name[len])
    {
        if (len >= 64)
            break;
        bool is_digit = name[len] >= '0' && name[len] <= '9';
        bool is_alpha = name[len] >= 'a' && name[len] <= 'z';
        bool is_dash = name[len] == '-';
        bool is_underscore = name[len] == '_';
        is_dash = is_dash || is_underscore;
        if (!(is_digit || is_alpha || is_dash))
            break;
        len++;
    }
    *p_len = len;
    return name;
}