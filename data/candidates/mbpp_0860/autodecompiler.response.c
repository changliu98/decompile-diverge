char *func0(char *name)
{
    char *result;
    regex_t regex;
    int reti;
    regmatch_t matches[1];
    char *pattern = "[a-zA-Z0-9]$";
    reti = regcomp(&regex, pattern, 1);
    if( reti )
    {
        result = "Error compiling regex";
    }
    else
    {
        reti = regexec(&regex, name, 1, matches, 0);
        regfree(&regex);
        if( !reti )
        {
            result = "Accept";
        }
        else
        {
            result = "Discard";
        }
    }
    return result;
}