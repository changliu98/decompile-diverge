int sdscmp(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t minlen = (len1 < len2)? len1 : len2;
    int ret, cmp = strncmp(s1, s2, minlen);
    if (cmp == 0) {
        ret = (len1 > len2)? 1 : ((len1 < len2)? -1 : 0);
    } else {
        ret = cmp;
    }
    return ret;
}