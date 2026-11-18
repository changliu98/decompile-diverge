static _Bool cwk_path_is_string_equal(char *str1, char *str2, unsigned long len1, unsigned long len2)
{
    if (len1 != len2)
        return 0;
    if (path_style == PATH_DOS)
        return !str_is_subpath_dos(str1, str2, len1);
    for ( ; ; str1++, str2++, len1--)
    {
        int c1; int c2;
        _Bool b1; _Bool b2;
        if (str1[0] == '\0' && str2[0] == '\0')
            return 1;
        if (str1[0] == '\0' || str2[0] == '\0')
            return 0;
        if (len1 == 0)
            return 0;
        b1 = b2 = 0;
        if (str_is_separator(separators[path_style], str1[0]))
        {
            b1 = str_is_separator(separators[path_style], str2[0]) != 0;
        }
        c1 = str_is_path_char(str1[0]);
        c2 = str_is_path_char(str2[0]);
        if (c1 != c2 && !b1)
            return 0;
    }
    return 0;
}