const char* func0(const char* input) {
    regex_t regex;
    int ret;
    regmatch_t match[1];
    const char* pattern = "^[A-Z][a-z]*$"; // Inferred from string offset 0x2004
    const char* result;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        result = "Compilation failed"; // Inferred from string offset 0x2011
    } else {
        ret = regexec(&regex, input, 1, match, 0);
        regfree(&regex);
        
        if (ret == 0) {
            result = "true"; // Inferred from string offset 0x2027
        } else {
            result = "false"; // Inferred from string offset 0x202e
        }
    }

    return result;
}