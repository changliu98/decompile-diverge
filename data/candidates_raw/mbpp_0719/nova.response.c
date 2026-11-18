static const char *func0(const char *name) {
    regex_t r;
    const char *cp;
    int rv;

    rv = regcomp(&r, "[^A-Za-z0-9_]", REG_EXTENDED);
    if (rv!= 0)
        cp = "\\&";
    else {
        char buf[100];
        rv = regexec(&r, name, 0, NULL, 0);
        regfree(&r);
        if (rv == 0)
            cp = "\\&";
        else
            cp = "\\\\";
    }
    return cp;
}