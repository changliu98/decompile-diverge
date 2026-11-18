const char *func0(char **patterns, int count, char *str) {
    regex_t regex;
    int ret;
    int i;
    const char *result;

    for (i = 0; i < count; i++) {
        ret = regcomp(&regex, patterns[i], 0);
        if (ret != 0) {
            fprintf(stderr, "Failed to compile regex\n");
            result = "no";
            return result;
        }
        ret = regexec(&regex, str, 0, NULL, 0);
        if (ret == 0) {
            regfree(&regex);
            result = "yes";
            return result;
        }
        regfree(&regex);
    }
    result = "no";
    return result;
}