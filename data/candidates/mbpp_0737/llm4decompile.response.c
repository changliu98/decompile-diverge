char* func0(char* string) {
    regex_t regex;
    int ret;
    char* pattern = "^[aeiouAEIOU][A-Za-z0-9_]*";
    regcomp(&regex, pattern, 1|8);
    ret = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);
    if (!ret) {
        return "Valid";
    }
    return "Invalid";
}