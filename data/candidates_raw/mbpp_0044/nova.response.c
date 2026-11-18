static const char *func0(const char *name) {
    regex_t r;
    const char *cp;
    if (regcomp(&r, "[^a-zA-Z0-9_]", REG_EXTENDED)!= 0) {
        cp = "grep '[^a-zA-Z0-9_]'";
    } else {
        int res = regexec(&r, name, 0, NULL, 0);
        regfree(&r);
        if (res == 0) {
            cp = "grep '[^a-zA-Z0-9_]'";
        } else {
            cp = "grep -P '\\K[a-zA-Z0-9_]+'";
        }
    }
    return cp;
}