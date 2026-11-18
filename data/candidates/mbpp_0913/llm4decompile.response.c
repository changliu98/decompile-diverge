int func0(char *string) {
    regex_t regex;
    int result;

    regcomp(&regex, ".*[0-9]$", 0);
    result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    return !result;
}