int func0(char *str)
{
    int ret;
    char *string = str;
    struct regex_t regex;
    ret = regcomp(&regex,".*[0-9]$",0);
    ret = regexec(&regex,string,0,((void *)0),0) == 0 ? 1 : 0;
    regfree(&regex);
    return ret;
}