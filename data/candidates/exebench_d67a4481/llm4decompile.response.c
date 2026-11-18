int Utf8ToUnicode(const char *utf8char, int *unicode, int *len, size_t leaveLen)
{
    if ((utf8char[0] & 0xf8) == 0xf0) {
        if (leaveLen < 4 || (utf8char[1] & 0xc0) != 0x80 || (utf8char[2] & 0xc0) != 0x80 || (utf8char[3] & 0xc0) != 0x80) {
            return 2;
        }
        *len = 4;
        *unicode = (*unicode << 6) | (utf8char[0] & 0x07);
        *unicode = (*unicode << 6) | (utf8char[1] & 0x3f);
        *unicode = (*unicode << 6) | (utf8char[2] & 0x3f);
        *unicode = (*unicode << 6) | (utf8char[3] & 0x3f);
    } else if ((utf8char[0] & 0xf0) == 0xe0) {
        if (leaveLen < 3 || (utf8char[1] & 0xc0) != 0x80 || (utf8char[2] & 0xc0) != 0x80) {
            return 2;
        }
        *len = 3;
        *unicode = (*unicode << 6) | (utf8char[0] & 0x0f);
        *unicode = (*unicode << 6) | (utf8char[1] & 0x3f);
        *unicode = (*unicode << 6) | (utf8char[2] & 0x3f);
    } else if ((utf8char[0] & 0xe0) == 0xc0) {
        if (leaveLen < 2 || (utf8char[1] & 0xc0) != 0x80) {
            return 2;
        }
        *len = 2;
        *unicode = (*unicode << 6) | (utf8char[0] & 0x1f);
        *unicode = (*unicode << 6) | (utf8char[1] & 0x3f);
    } else if ((utf8char[0] & 0x80) == 0x00) {
        *len = 1;
        *unicode = utf8char[0];
    } else {
        return 1;
    }

    return 0;
}