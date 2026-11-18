char *func0(char *dst, const char *src) {
    char *ret = dst;
    for (; (*dst = *src); ++src, ++dst)
        continue;
    return ret;
}