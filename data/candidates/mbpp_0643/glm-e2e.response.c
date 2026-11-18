const char* func0(const char* input) {
    regex_t regex;
    int ret;
    char errbuf[100];
    const char* result;
    const char* pattern = "^[A-Za-z0-9_]+$"; // Inferred from typical usage, exact string in .rodata

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        fprintf(stderr, "Could not compile regex\n");
        result = "Compilation failed";
        return result;
    }

    ret = regexec(&regex, input, 0, NULL, 0);
    if (ret == 0) {
        result = "Match";
    } else if (ret == REG_NOMATCH) {
        result = "No match";
    } else {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex match failed: %s\n", errbuf);
        result = "Execution failed";
    }

    return result;
}