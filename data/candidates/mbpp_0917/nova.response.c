static const char *func0(const char *name) {
    regex_t r;
    regcomp(&r, "^[a-zA-Z0-9_]+$", REG_EXTENDED);
    int result = regexec(&r, name, 0, NULL, 0);
    const char *err;
    if (result == 0) {
        err = "No error";
    } else {
        err = "Invalid character in name";
    }
    return err;
}