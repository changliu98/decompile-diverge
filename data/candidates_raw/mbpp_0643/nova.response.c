static const char *func0(const char *fmt) {
    static char buf[100];
    static char fmt2[100];
    static char *p = fmt2;
    char *p2;
    int r;

    r = sscanf(p, fmt, buf, &p2);
    if (r!= 0) {
        fprintf(stderr, "%s\n", buf);
        p = p2;
        return buf;
    }
    r = sscanf(p, fmt, &p2);
    if (r == 0) {
        return "0";
    }
    if (r == 1) {
        return "1";
    }
    snprintf(buf, sizeof buf, fmt, p2, &p2);
    fprintf(stderr, "%s\n", buf);
    p = p2;
    return buf;
}