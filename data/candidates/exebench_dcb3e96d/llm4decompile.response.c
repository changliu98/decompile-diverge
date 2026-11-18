void utf8_encode(uint32_t val, unsigned char *utf8_str)
{
    int len = 0;

    if (val < 0x80) {
        utf8_str[0] = val;
        len = 1;
    } else if (val < 0x800) {
        utf8_str[0] = 0xC0 | (val >> 6);
        utf8_str[1] = 0x80 | (val & 0x3F);
        len = 2;
    } else if (val < 0x8000) {
        utf8_str[0] = 0xE0 | (val >> 12);
        utf8_str[1] = 0x80 | ((val >> 6) & 0x3F);
        utf8_str[2] = 0x80 | (val & 0x3F);
        len = 3;
    } else if (val < 0x110000) {
        utf8_str[0] = 0xF0 | (val >> 18);
        utf8_str[1] = 0x80 | ((val >> 12) & 0x3F);
        utf8_str[2] = 0x80 | ((val >> 6) & 0x3F);
        utf8_str[3] = 0x80 | (val & 0x3F);
        len = 4;
    }

    utf8_str[len] = '\0';
}