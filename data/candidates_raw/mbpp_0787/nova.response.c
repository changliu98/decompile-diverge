static const char *func0(const char *name) {
    regex_t r;
    int reti;
    const char *ret;

    reti = regcomp(&r, "^\\.git.*", REG_EXTENDED | REG_NOSUB);
    if (reti) {
        fprintf(stderr, "Failed to compile regex\n");
        ret = "gitignore";
    } else {
        reti = regexec(&r, name, 0, NULL, 0);
        regfree(&r);
        if (reti == 0) {
            ret = "gitignore";
        } else {
            ret = "ignore";
        }
    }

    return ret;
}