static int pjmedia_rtcp_fb_build_sli(const char *name, const char *value,
                            unsigned long *result, int maxlen,
                            const unsigned short *table)
{
    unsigned char *p;
    int i;
    unsigned int len;

    if (name == NULL || value == NULL || result == NULL || maxlen == 0 || table == NULL)
        goto err;
    len = maxlen * 4 + 3;
    if (len > *result)
        goto err;
    p = (unsigned char *)value;
    memcpy(p, name, 8);
    p[0] = (p[0] & ~0x20) | 0x10;
    p[0] = (p[0] & ~0x3f) | 0x02;
    p[1] = (p[1] & 0xff) | (len >> 16) << 8;
    p[2] = (p[2] & 0xff) | (len >> 8) << 16;
    p += 3;
    for (i = 0; i < maxlen; i++) {
        *p++ = (table[i] >> 5) & 0x3f;
        *p++ = (table[i] << 1) & 0xff;
        *p++ = (table[i] >> 10) & 0x03;
        *p++ = (table[i] >> 2) & 0xff;
        *p++ = (table[i] << 6) & 0xc0;
    }
    *result = len;
    return 0;
err:
    return TEST_error("pjmedia_rtcp_fb_build_sli", "bad arguments", 131, len);
}