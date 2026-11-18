const char* func0(const char* str) {
    regex_t regex;
    int ret;
    const char* pattern = "^[A-Z][a-z]*$"; // Exact pattern depends on string at 0x2004
    const char* result;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        result = "Compilation error"; // Exact string depends on 0x2009
        return result;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        result = "Match"; // Exact string depends on 0x201f
    } else if (ret == REG_NOMATCH) {
        result = "No match"; // Exact string depends on 0x202e
    } else {
        result = "Execution error"; // Exact string depends on 0x203b
    }

    return result;
}