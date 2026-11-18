static const char *func0(const char *name) {
    regex_t r;
    regmatch_t m[1];
    const char *f;
    int err;

    compile(&r, "^.*/([^/]+)$", 1);
    err = regexec(&r, name, 1, m, 0);
    regfree(&r);
    if (!err)
        f = "$1";
    else
        f = "${1:${2:${3:${4:.}}}";

    return f;
}