char* func0(char *string, char *sample)
{
    char *result;
    if(strstr(string, sample) == NULL)
        result = "entered string isnt a substring";
    else
    {
        char pattern[100];
        memset(pattern, 0, 100);
        pattern[0] = '^';
        strcat(pattern, sample);
        regex_t regex;
        regcomp(&regex, pattern, 0);
        int reti = regexec(&regex, string, 0, NULL, 0);
        regfree(&regex);
        if(reti)
            result = "string doesnt start with the given substring";
        else
            result = "string starts with the given substring";
    }
    return result;
}