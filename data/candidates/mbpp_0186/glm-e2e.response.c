const char* func0(const char *str, const char *pattern) {
    regex_t regex;
    int ret;
    const char *result;

    ret = regcomp(&regex, pattern, 0);
    if (ret != 0) {
        result = "Invalid regular expression";
    } else {
        ret = regexec(&regex, str, 0, NULL, 0);
        regfree(&regex);
        
        if (ret == 0) {
            result = "true";
        } else {
            result = "false";
        }
    }
    
    return result;
}