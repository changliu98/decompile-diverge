int func0(char *pattern, char *text, int *start, int *end)
{
    regex_t regex;
    int status;
    regmatch_t match;

    status = regcomp(&regex, pattern, 1);
    if (status != 0)
        return -1;

    status = regexec(&regex, text, 1, &match, 0);
    regfree(&regex);
    if (status != 0)
        return -1;

    *start = match.rm_so;
    *end = match.rm_eo;

    return 0;
}