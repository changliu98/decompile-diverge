int c_strcasecmp(const char *s1, const char *s2) {
    const char *p1 = s1;
    const char *p2 = s2;
    int ret = 0;

    if (p1 == p2) {
        return 0;
    }

    while (1) {
        char c1 = (char)c_tolower((unsigned char)*p1);
        char c2 = (char)c_tolower((unsigned char)*p2);

        if (c1 == '\0' || c1 != c2) {
            ret = (unsigned char)c1 - (unsigned char)c2;
            break;
        }

        p1++;
        p2++;
    }

    return ret;
}