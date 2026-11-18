int unicode_to_utf8(char *p, unsigned int c)
{
    char *_p = p;

    if (c < 0x80) {
        *p++ = (char)c;
    } else if (c < 0x800) {
        *p++ = (c >> 6) | 0xC0;
        *p++ = (c & 0x3F) | 0x80;
    } else if (c < 0x10000) {
        *p++ = (c >> 12) | 0xE0;
        *p++ = ((c >> 6) & 0x3F) | 0x80;
        *p++ = (c & 0x3F) | 0x80;
    } else if (c < 0x200000) {
        *p++ = (c >> 18) | 0xF0;
        *p++ = ((c >> 12) & 0x3F) | 0x80;
        *p++ = ((c >> 6) & 0x3F) | 0x80;
        *p++ = (c & 0x3F) | 0x80;
    } else if (c < 0x4000000) {
        *p++ = (c >> 24) | 0xF8;
        *p++ = ((c >> 18) & 0x3F) | 0x80;
        *p++ = ((c >> 12) & 0x3F) | 0x80;
        *p++ = ((c >> 6) & 0x3F) | 0x80;
        *p++ = (c & 0x3F) | 0x80;
    } else {
        *p++ = (c >> 30) | 0xFC;
        *p++ = ((c >> 24) & 0x3F) | 0x80;
        *p++ = ((c >> 18) & 0x3F) | 0x80;
        *p++ = ((c >> 12) & 0x3F) | 0x80;
        *p++ = ((c >> 6) & 0x3F) | 0x80;
        *p++ = (c & 0x3F) | 0x80;
    }
    *p = '\0';

    return (int)(p - _p);
}