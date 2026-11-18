char *is_name(char *text)
{
    int ret;
    char *name = text;
    struct regex_t reg;
    regcomp(&reg, "[A-Z]+[a-z]+$", 1);
    ret = regexec(&reg, name, 0, ((void *)0), 0);
    regfree(&reg);
    if (ret)
        return "No";
    return "Yes";
}