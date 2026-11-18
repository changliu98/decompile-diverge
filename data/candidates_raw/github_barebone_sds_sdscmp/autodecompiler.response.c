int sdscmp(sds s1, sds s2) {
    size_t l1, l2, minlen;
    int cmp;
    l1 = sdslen(s1);
    l2 = sdslen(s2);

    if (l1 < l2) {
        minlen = l1;
    } else {
        minlen = l2;
    }
    cmp = memcmp(s1,s2,minlen);
    if (cmp == 0) {
        if (l1 > l2)
            return 1;
        else if (l1 < l2)
            return -1;
        else
            return 0;
    }
    return cmp;
}