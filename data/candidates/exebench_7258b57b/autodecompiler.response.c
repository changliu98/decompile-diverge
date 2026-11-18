static int
UnicodeToUtf8(unsigned int ch, char *buf)
{
    int len = 0;

    if (ch < 0x80) {
        *buf++ = (char)ch;
        len = 1;
    } else if (ch < 0x800) {
        *buf++ = (ch >> 6) | 0xc0;
        *buf++ = (ch & 0x3f) | 0x80;
        len = 2;
    } else if (ch == 0xfeff) {

    } else if (ch >= 0xd800 && ch <= 0xdfff) {

    } else if (ch < 0x10000) {
        *buf++ = (ch >> 12) | 0xe0;
        *buf++ = ((ch >> 6) & 0x3f) | 0x80;
        *buf++ = (ch & 0x3f) | 0x80;
        len = 3;
    } else if (ch < 0x110000) {
        *buf++ = (ch >> 18) | 0xf0;
        *buf++ = ((ch >> 12) & 0x3f) | 0x80;
        *buf++ = ((ch >> 6) & 0x3f) | 0x80;
        *buf++ = (ch & 0x3f) | 0x80;
        len = 4;
    } else {

    }

    *buf = '\0';
    return len;
}