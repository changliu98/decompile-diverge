int c_strncasecmp(const char *s1, const char *s2, size_t n) {
    const char *p1 = s1;
    const char *p2 = s2;
    int ret;

    if (p1 == p2 || n == 0) {
        ret = 0;
        return ret;
    }

    while (1) {
        char c1 = (char)c_tolower((unsigned char)*p1);
        char c2 = (char)c_tolower((unsigned char)*p2);
        
        n--;
        
        if (n == 0 || c1 == '\0' || c1 != c2) {
            ret = (unsigned char)c1 - (unsigned char)c2;
            break;
        }
        
        p1++;
        p2++;
    }

    return ret;
}