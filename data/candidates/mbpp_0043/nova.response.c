static const char *func0(const char *name) {
    static char buf[100];
    char path[PATH_MAX];
    const char *result;
    int ret;

    ret = snprintf(path, sizeof(path), "%s/%s", sysfs_gpio_base, name);
    if (ret) {
        fprintf(stderr, "snprintf failed: %d\n", ret);
        result = "<error>";
    } else {
        ret = readlink(path, buf, sizeof(buf));
        if (ret == 0) {
            free(buf);
            result = "<error>";
        } else if (ret == 1) {
            free(buf);
            result = "<unknown>";
        } else {
            buf[ret] = 0;
            fprintf(stderr, "%s: %s\n", path, buf);
            result = buf;
        }
    }
    return result;
}