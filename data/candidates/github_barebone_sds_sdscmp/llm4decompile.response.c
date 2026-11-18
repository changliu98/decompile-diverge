int sdscmp(const sds s1, const sds s2) {
    size_t s1len = sdslen(s1), s2len = sdslen(s2), minlen = (s1len < s2len) ? s1len : s2len;
    int cmp;

    cmp = memcmp(s1,s2,minlen);
    if (cmp == 0) { return (s1len > s2len) - (s1len < s2len); }
    return cmp;
}