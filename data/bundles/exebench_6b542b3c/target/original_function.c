static char *trim(char *str, char *trim_chars)
{
    char *endstr;

    if(!str)
        return str;

    endstr = index(str, 0) - 1;

    while(endstr >= str && index(trim_chars, *endstr))
    {
        *endstr = 0;
        endstr--;
    }

    return str;
}