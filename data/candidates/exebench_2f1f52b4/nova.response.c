int isLegalUTF8(const unsigned char *s, int len)
{
    const unsigned char *p = s + len;
    unsigned char c1, c2;
    int ret;

    p -= 3;
    do {
        c1 = *p--;
        if (c1 < 0x80)
            ret = 0;
        else if (c1 < 0xC2)
            ret = 0;
        else if (c1 < 0xE0)
            ret = 1;
        else if (c1 < 0xF0) {
            c2 = *p--;
            if (c2 < 0x80 || c2 > 0xBF)
                ret = 0;
            else if (c1 < 0xE1)
                ret = 0;
            else if (c1 < 0xF0)
                ret = 1;
            else if (c1 < 0xF5)
                ret = 1;
            else if (c1 < 0xF8)
                ret = 0;
            else if (c1 < 0xFC)
                ret = 1;
            else if (c1 < 0xFE)
                ret = 0;
            else
                ret = 1;
        } else if (c1 < 0xF5)
            ret = 0;
        else if (c1 < 0xF9)
            ret = 1;
        else if (c1 < 0xFD)
            ret = 0;
        else
            ret = 1;
    } while (ret);
    return ret;
}