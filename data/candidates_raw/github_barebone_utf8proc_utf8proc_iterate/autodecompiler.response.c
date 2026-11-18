int utf8proc_iterate(unsigned char *str, long len, int *uprv)
{
    *uprv = -1;

    if (len == 0) {
        ret = 0;
        goto done;
    }

    p = str;
    if (len < 0)
        left = sizeof(str);
    else
        left = len;

    unsigned char *end = p + left;

    c = *buf++;
    if (c < 0x80) {
        *uprv = c;
        ret = 1;
        goto done;
    }
    if (c >= 0xc2 && c <= 0xf4) {
        if (c < 0xe0) {
            if (p >= end || (*p & 0xc0) != 0x80) {
                ret = -3;
                goto done;
            }
            *uprv = ((c & 0x1f) << 6) | (*p & 0x3f);
            ret = 2;
            goto done;
        }
        if (c < 0xf0) {
            if (p + 1 >= end || (*p & 0xc0) != 0x80 || (*(p + 1) & 0xc0) != 0x80) {
                ret = -3;
                goto done;
            }
            if (c == 0xed && *p >= 0xa0) {
                ret = -3;
                goto done;
            }
            c = ((c & 0x0f) << 12) | ((*p & 0x3f) << 6) | (*(p + 1) & 0x3f);
            if (c < 0x800) {
                ret = -3;
                goto done;
            }
            *uprv = c;
            ret = 3;
            goto done;
        }
        if (p + 2 >= end || (*p & 0xc0) != 0x80 || (*(p + 1) & 0xc0) != 0x80 || (*(p + 2) & 0xc0) != 0x80) {
            ret = -3;
            goto done;
        }
        if (c == 0xf0 && *p < 0x90) {
            ret = -3;
            goto done;
        }
        if (c == 0xf4 && *p > 0x8f) {
            ret = -3;
            goto done;
        }
        *uprv = ((c & 0x07) << 18) | ((*p & 0x3f) << 12) | ((*(p + 1) & 0x3f) << 6) | (*(p + 2) & 0x3f);
        ret = 4;
    } else {
        ret = -3;
    }

done:
    return ret;
}