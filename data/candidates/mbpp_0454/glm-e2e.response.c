const char* func0(const char* input) {
    regex_t regex;
    int ret;
    char errbuf[100];
    const char* result;

    ret = regcomp(&regex, "^-?\\d+$", 1);
    if (ret != 0) {
        fprintf(stderr, "Could not compile regex\n");
        result = "Invalid";
    } else {
        ret = regexec(&regex, input, 0, NULL, 0);
        regfree(&regex);

        if (ret == 0) {
            result = "Integer";
        } else if (ret == 1) {
            result = "Not an integer";
        } else {
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Regex match failed: %s\n", errbuf);
            result = "Error";
        }
    }

    return result;
}