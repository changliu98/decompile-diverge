static int get_utf8(char *str, int len, int pos, int *bytes)
{
    int c = 0;

    if ((pos < len - 1) && ((str[pos] & 0xe0) == 0xc0) && ((str[pos + 1] & 0xc0) == 0x80)) {
        *bytes = 2;
        c = str[pos] & 0x1f;
        c <<= 6;
        c += str[pos + 1] & 0x3f;
        if (c < 0x80)
            c = 0;
    } else if ((pos < len - 2) && ((str[pos] & 0xf0) == 0xe0) && ((str[pos + 1] & 0xc0) == 0x80) && ((str[pos + 2] & 0xc0) == 0x80)) {
        *bytes = 3;
        c = str[pos] & 0x0f;
        c <<= 6;
        c += str[pos + 1] & 0x3f;
        c <<= 6;
        c += str[pos + 2] & 0x3f;
        if (c < 0x800)
            c = 0;
    } else if ((pos < len - 3) && ((str[pos] & 0xf8) == 0xf0) && ((str[pos + 1] & 0xc0) == 0x80) && ((str[pos + 2] & 0xc0) == 0x80) && ((str[pos + 3] & 0xc0) == 0x80)) {
        *bytes = 4;
        c = str[pos] & 0x07;
        c <<= 6;
        c += str[pos + 1] & 0x3f;
        c <<= 6;
        c += str[pos + 2] & 0x3f;
        c <<= 6;
        c += str[pos + 3] & 0x3f;
        if (c < 0x10000)
            c = 0;
    }
    return c;
}