int func0(const char *str) {
    regex_t regex;
    int ret;
    char result;

    // Compile the regular expression
    // The string is located at 0x2004, which is typically a simple pattern like "^pattern$"
    ret = regcomp(&regex, "pattern", 0);
    if (ret != 0) {
        fprintf(stderr, "Could not compile regex\n");
        result = 0;
    } else {
        // Execute the regular expression
        ret = regexec(&regex, str, 0, NULL, 0);
        regfree(&regex);
        
        if (ret == 0) {
            result = 1;
        } else {
            result = 0;
        }
    }

    return result & 1;
}