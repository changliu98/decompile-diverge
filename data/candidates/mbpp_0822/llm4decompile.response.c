int func0(char *str)
{
    int len = strlen(str);
    int i;
    int hasLower = 0;
    int hasUpper = 0;
    int hasDigit = 0;
    int hasSpecial = 0;

    if (len < 6 || len > 12)
        return 0;

    for (i = 0; i < len; i++)
    {
        if ((*__ctype_b_loc ())[(int) ((str[i]))] & (0x0200))
            hasLower = 1;
        else if ((*__ctype_b_loc ())[(int) ((str[i]))] & (0x0100))
            hasUpper = 1;
        else if ((*__ctype_b_loc ())[(int) ((str[i]))] & (0x0800))
            hasDigit = 1;
        else if (str[i] == '$' || str[i] == '#' || str[i] == '@')
            hasSpecial = 1;
        else if ((*__ctype_b_loc ())[(int) ((str[i]))] & (0x2000))
            return 0;
    }

    if (hasLower && hasUpper && hasDigit && hasSpecial)
        return 1;

    return 0;
}