void encode_int(char *buf, int num)
{
    int negative;

    negative = 0;
    if (num <= 0) {
        negative = 1;
        num = -num;
    }
    if (num > 0x7c00) {
        *buf++ = 0x40 | ((num >> 10) & 0x1f);
    }
    if (num > 0x3f0) {
        *buf++ = 0x40 | ((num >> 4) & 0x3f);
    }
    if (num & 0xf) {
        *buf++ = 0x20 | (num & 0xf);
    } else {
        *buf++ = ' ';
    }
    if (!negative) {
        *buf++ |= 0x10;
    }
    *buf = '\0';
}