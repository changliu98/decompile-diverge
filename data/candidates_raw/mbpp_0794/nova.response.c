static const char *func0(const char *name) {
    regex_t r;
    int reti;
    const char *ret;

    reti = regcomp(&r, "^\\s*\\w+\\s*=\\s*(.*)\\s*$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Failed to compile regex\n");
        ret = "ERROR_REGEX";
    } else {
        reti = regexec(&r, name, 0, NULL, 0);
        regfree(&r);
        if (reti == 0) {
            ret = "MATCH";
        } else {
            ret = "NO_MATCH";
        }
    }

    return ret;
}