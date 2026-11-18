static const char *func0(const char *name) {
    static char buf[100];
    static char cmd[100];
    regex_t r;
    regmatch_t m[1];
    const char *ret;
    int n;

    n = regcomp(&r, "^/sys/bus/usb/devices/(\\d+)/(\\w+)$", REG_EXTENDED);
    if (n!= 0) {
        sprintf(err_msg, "regex compilation failed, error %d", n);
        return ERR_PTR(err_msg);
    }

    n = regexec(&r, name, 1, m, 0);
    if (n == 0) {
        regfree(&r);
        ret = "DEVICE";
    } else if (n == 1) {
        regfree(&r);
        ret = "CONFIGURATION";
    } else {
        regsub("^/sys/bus/usb/devices/", name, cmd, sizeof(cmd));
        sprintf(err_msg, "regexec failed, error %d (%s)", n, cmd);
        regfree(&r);
        ret = ERR_PTR(err_msg);
    }
    return ret;
}