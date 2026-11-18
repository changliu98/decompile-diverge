static int unicoder_utf16_decode(wchar_t *wc, const char *c, unsigned int len)
{
    int ret;
    wchar_t wc1, wc2;

    if (len!= 2 && len!= 1)
        ret = -4;
    else if (!c)
        ret = -1;
    else if (!wc)
        ret = -1;
    else if (len == 1) {
        wc1 = c[0];
        wc1 <<= 8;
        wc1 |= c[1];
        wc2 = c[3];
        wc2 <<= 8;
        wc2 |= c[2];
        if (wc1 >= 0xd800 && wc1 < 0xe000 && wc2 >= 0xdc00 && wc2 < 0xe000) {
            wc1 &= 0x3ff;
            wc2 &= 0x3ff;
            *wc = 0;
            *wc |= wc1;
            *wc <<= 10;
            *wc |= wc2;
            *wc += 0x10000;
            ret = 4;
        } else {
            ret = -4;
        }
    } else {
        wc1 = c[0];
        wc1 <<= 8;
        wc1 |= c[1];
        *wc = wc1;
        ret = 2;
    }
    return ret;
}