static const char *func0(const char *name) {
    static char buf[100];
    static char *p = NULL;
    char *path;
    int r;

    if ((r = asprintf(&path, "%s/%s", sysfs_gpio_base, name))!= 0) {
        fprintf(stderr, "asprintf() failed: %s\n", strerror(errno));
        return "<error>";
    }

    r = read_file(path, buf, sizeof(buf), 0);
    free(path);
    if (r == 0)
        return "<unknown>";
    else if (r == 1)
        return "<ok>";
    else {
        char *s = buf;
        trim_end(&s);
        asprintf(&p, "%s", s);
        return p;
    }
}