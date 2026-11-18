void func0(unsigned char *p, const BIGNUM *x, const BIGNUM *y)
{
    unsigned char xbuf[64], ybuf[64];

    memcpy(xbuf, pad_zeroes, sizeof(xbuf));
    memcpy(xbuf + sizeof(xbuf) - 1, x, sizeof(xbuf));
    memcpy(ybuf, pad_zeroes, sizeof(ybuf));
    memcpy(ybuf + sizeof(ybuf) - 1, y, sizeof(ybuf));
    memcpy(p, xbuf, sizeof(xbuf));
    memcpy(p + sizeof(xbuf), ybuf, sizeof(ybuf));
    memset(p + sizeof(xbuf) + sizeof(ybuf), 0x40, 64);
}