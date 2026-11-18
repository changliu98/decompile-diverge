const char* func0(const char* arg) {
    regex_t regex;
    int ret;
    const char* result;

    ret = regcomp(&regex, "a", REG_ICASE);
    if (ret != 0) {
        result = "Invalid regular expression";
    } else {
        ret = regexec(&regex, arg, 0, NULL, 0);
        regfree(&regex);
        if (ret == 0) {
            result = "Match found";
        } else {
            result = "No match";
        }
    }

    return result;
}