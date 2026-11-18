char *strcpy(char *dst, const char *src) {
    char *ret = dst;
    for (; (*dst = *src); ++src, ++dst)
        continue;
    return ret;
}