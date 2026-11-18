void utf8_int_string(uint32_t chr, char *str) {
    if (str == 0) {
        return;
    }

    str[0] = '\0';

    if (chr <= 0x7f) {
        str[0] = (char)chr;
        str[1] = '\0';
    } else if (chr <= 0x7ff) {
        str[0] = (char)(0xc0 | (chr >> 6));
        str[1] = (char)(0x80 | (chr & 0x3f));
        str[2] = '\0';
    } else if (chr <= 0xffff) {
        str[0] = (char)(0xe0 | (chr >> 12));
        str[1] = (char)(0x80 | ((chr >> 6) & 0x3f));
        str[2] = (char)(0x80 | (chr & 0x3f));
        str[3] = '\0';
    } else if (chr <= 0x1fffff) {
        str[0] = (char)(0xf0 | (chr >> 18));
        str[1] = (char)(0x80 | ((chr >> 12) & 0x3f));
        str[2] = (char)(0x80 | ((chr >> 6) & 0x3f));
        str[3] = (char)(0x80 | (chr & 0x3f));
        str[4] = '\0';
    }
}