int
UnicodeToUtf8(uint32_t unicode, char *dest)
{
    int len = 0;

    if (unicode < 0x80) {
        *dest++ = (char) unicode;
        len = 1;
    } else if (unicode < 0x800) {
        *dest++ = 0xc0 | ((unicode >> 6) & 0x1f);
        *dest++ = 0x80 | (unicode & 0x3f);
        len = 2;
    } else if (unicode == 0xfeff) {

    } else if (unicode >= 0xd800 && unicode <= 0xdfff) {

    } else if (unicode < 0x10000) {
        *dest++ = 0xe0 | ((unicode >> 12) & 0x0f);
        *dest++ = 0x80 | ((unicode >> 6) & 0x3f);
        *dest++ = 0x80 | (unicode & 0x3f);
        len = 3;
    } else if (unicode < 0x10000) {
        *dest++ = 0xf0 | ((unicode >> 18) & 0x07);
        *dest++ = 0x80 | ((unicode >> 12) & 0x3f);
        *dest++ = 0x80 | ((unicode >> 6) & 0x3f);
        *dest++ = 0x80 | (unicode & 0x3f);
        len = 4;
    }

    *dest = '\0';

    return len;
}