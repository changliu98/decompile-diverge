static const char *func0(const char *name) {
    regex_t r;
    regcomp(&r, "[a-zA-Z_][a-zA-Z0-9_]*", REG_EXTENDED);
    int match = regexec(&r, name, 0, NULL, 0);
    regfree(&r);
    const char *res;
    if (match == 0) {
        res = "<span class=\"c\">";
    } else {
        res = "<span class=\"nx\">";
    }
    return res;
}