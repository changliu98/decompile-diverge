int func0(char *string) {
    int ret;
    regex_t regex;

    regcomp(&regex, "[^a-zA-Z0-9.]", 1);
    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (ret == 1)
        return 1;
    else
        return 0;
}