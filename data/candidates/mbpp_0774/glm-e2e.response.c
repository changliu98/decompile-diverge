const char* func0(const char* str) {
    regex_t regex;
    int ret;
    const char* pattern = "^[-+]?[0-9]+[ ]*$";
    const char* result;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        result = "Invalid";
        return result;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        result = "Valid";
    } else {
        result = "Invalid";
    }

    return result;
}