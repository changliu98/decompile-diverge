size_t sdsrange(char *dst, ssize_t dstlen, ssize_t cpylen) {
    size_t len = strlen(dst);
    if (len == 0)
        return 0;

    if (dstlen > 0) {
        dstlen += len;
        if (dstlen < 0)
            dstlen = 0;
    }

    if (cpylen > 0) {
        cpylen += len;
        if (cpylen < 0)
            cpylen = 0;
    }

    size_t n;
    if (dstlen > cpylen)
        n = 0;
    else
        n = cpylen - dstlen + 1;

    if (n!= 0) {
        if (dstlen < len)
            n = 0;
        else {
            if (cpylen < len)
                cpylen = len - 1;
            else
                cpylen -= len;
            n = cpylen - dstlen + 1;
        }
    }

    if (dstlen!= 0 && n!= 0)
        memmove(dst + dstlen, dst, n);
    dst[n] = '\0';
    return strlen(dst);
}