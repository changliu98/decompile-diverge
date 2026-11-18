const char* func0(const char* str) {
    regex_t regex;
    const char* pattern = "^[A-Z][a-z]+$";
    int ret;
    const char* result;

    regcomp(&regex, pattern, REG_EXTENDED);
    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        result = "Yes";
    } else {
        result = "No";
    }

    return result;
}