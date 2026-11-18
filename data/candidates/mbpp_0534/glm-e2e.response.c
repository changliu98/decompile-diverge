int func0(const char *pattern, const char *string, regmatch_t *match1, regmatch_t *match2) {
    regex_t regex;
    int ret;
    regmatch_t matches[1];

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return -1;
    }

    ret = regexec(&regex, string, 1, matches, 0);
    regfree(&regex);

    if (ret != 0) {
        return -1;
    }

    *match1 = matches[0];
    *match2 = matches[0];

    return 0;
}