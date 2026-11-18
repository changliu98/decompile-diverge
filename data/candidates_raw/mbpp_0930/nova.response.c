static const char *func0(const char *name) {
    regex_t r;
    int reti;
    const char *ret;

    reti = regcomp(&r, "^\\.?\\/", REG_EXTENDED | REG_NOSUB);
    if (reti) {
        ret = "Invalid regex";
    } else {
        reti = regexec(&r, name, 0, NULL, 0);
        regfree(&r);
        if (reti == 0) {
            ret = "is an absolute path";
        } else if (reti == REG_NOMATCH) {
            ret = "is a relative path";
        } else {
            ret = "regcomp/regexec failed";
        }
    }

    return ret;
}