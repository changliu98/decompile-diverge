static const char *func0(const char *name) {
    regex_t r;
    const char *result;
    if (regcomp(&r, "^[a-zA-Z0-9_]+$", REG_EXTENDED) == 0) {
        if (regexec(&r, name, 0, NULL, 0) == 0) {
            result = "text";
        } else {
            result = "binary";
        }
        regfree(&r);
    } else {
        result = "binary";
    }
    return result;
}