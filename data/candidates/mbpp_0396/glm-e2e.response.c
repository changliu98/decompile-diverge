const char* func0(const char* arg) {
    regex_t regex;
    int ret;
    char errbuf[100];
    const char* result;

    ret = regcomp(&regex, "^[a-z]+$", REG_EXTENDED);
    if (ret != 0) {
        fprintf(stderr, "Could not compile regex\n");
        result = "Invalid";
    } else {
        ret = regexec(&regex, arg, 0, NULL, 0);
        if (ret == 0) {
            regfree(&regex);
            result = "Valid";
        } else if (ret == REG_NOMATCH) {
            regfree(&regex);
            result = "Invalid";
        } else {
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Regex match failed: %s\n", errbuf);
            regfree(&regex);
            result = "Invalid";
        }
    }

    return result;
}