char *isPalindrome(char *str)
{
    int ret;
    char *str1 = str;
    char errormsg[100];
    struct regex_t regex;
    if (regcomp(&regex, "^[a-z]$|^([a-z]).*\\1$", 1))
    {
        fprintf(stderr, "Could not compile regex\n");
        return "Invalid";
    }
    ret = regexec(&regex, str1, 0, ((void *)0), 0);
    if (ret == 0)
    {
        regfree(&regex);
        return "Valid";
    }
    else if (ret == 1)
    {
        regfree(&regex);
    }
    else
    {
        regerror(ret, &regex, errormsg, sizeof(errormsg));
        fprintf(stderr, "Regex match failed: %s\n", errormsg);
        regfree(&regex);
    }
    return "Invalid";
}