int memcasecmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *us1 = (const unsigned char *)s1;
    const unsigned char *us2 = (const unsigned char *)s2;
    int ret, tmp;
    size_t k;

    for (k = 0; k < n; k++) {
        if ((tmp = (int)tolower(us1[k]) - (int)tolower(us2[k]))!= 0) {
            ret = tmp;
            break;
        }
    }
    return ret;
}