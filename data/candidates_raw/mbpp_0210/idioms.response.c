int is_valid_name(char *name)
{
    struct regex_t regex;
    int ret;
    regcomp(&regex, "[^a-zA-Z0-9.]", 1);
    ret = regexec(&regex, name, 0, ((void *)0), 0);
    regfree(&regex);
    return ret == 1 ? 1 : 0;
}