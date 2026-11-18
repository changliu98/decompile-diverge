const char* func0(const char* str) {
    regex_t regex;
    regmatch_t match;
    const char* pattern = "^[A-Z][a-z]*$"; // 0x2004
    const char* result;

    if (regcomp(&regex, pattern, REG_EXTENDED) == 0) {
        if (regexec(&regex, str, 1, &match, 0) == 0) {
            regfree(&regex);
            result = "true"; // 0x200c
        } else {
            regfree(&regex);
            result = "false"; // 0x201b
        }
    } else {
        result = "error"; // 0x2028
    }

    return result;
}