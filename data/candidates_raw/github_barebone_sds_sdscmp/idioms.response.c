int sdscmp(struct sds s1, struct sds s2)
{
    unsigned long l1 = sdslen(s1);
    unsigned long l2 = sdslen(s2);
    unsigned long minlen = (l1 < l2 ? l1 : l2);
    int res = memcmp(s1.data, s2.data, minlen);
    if (res)
        return res;
    if (l1 > l2)
        return 1;
    if (l1 < l2)
        return -1;
    return 0;
}