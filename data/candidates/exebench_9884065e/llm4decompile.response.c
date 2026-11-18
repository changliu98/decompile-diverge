char* _PL__utf8_get_char(char* in, int* chr) {
    if ((((int)in[0] & 0xE0) == 0xC0) && (((int)in[1] & 0xC0) == 0x80)) {
        *chr = ((int)in[0] & 0x1F) << 6 | ((int)in[1] & 0x3F);
        in += 2;
    } else if ((((int)in[0] & 0xF0) == 0xE0) && (((int)in[1] & 0xC0) == 0x80) && (((int)in[2] & 0xC0) == 0x80)) {
        *chr = ((int)in[0] & 0x0F) << 12 | ((int)in[1] & 0x3F) << 6 | ((int)in[2] & 0x3F);
        in += 3;
    } else if ((((int)in[0] & 0xF8) == 0xF0) && (((int)in[1] & 0xC0) == 0x80) && (((int)in[2] & 0xC0) == 0x80) && (((int)in[3] & 0xC0) == 0x80)) {
        *chr = ((int)in[0] & 0x07) << 18 | ((int)in[1] & 0x3F) << 12 | ((int)in[2] & 0x3F) << 6 | ((int)in[3] & 0x3F);
        in += 4;
    } else if ((((int)in[0] & 0xFC) == 0xF8) && (((int)in[1] & 0xC0) == 0x80) && (((int)in[2] & 0xC0) == 0x80) && (((int)in[3] & 0xC0) == 0x80) && (((int)in[4] & 0xC0) == 0x80)) {
        *chr = ((int)in[0] & 0x03) << 24 | ((int)in[1] & 0x3F) << 18 | ((int)in[2] & 0x3F) << 12 | ((int)in[3] & 0x3F) << 6 | ((int)in[4] & 0x3F);
        in += 5;
    } else if ((((int)in[0] & 0xFE) == 0xFC) && (((int)in[1] & 0xC0) == 0x80) && (((int)in[2] & 0xC0) == 0x80) && (((int)in[3] & 0xC0) == 0x80) && (((int)in[4] & 0xC0) == 0x80) && (((int)in[5] & 0xC0) == 0x80)) {
        *chr = ((int)in[0] & 0x01) << 30 | ((int)in[1] & 0x3F) << 24 | ((int)in[2] & 0x3F) << 18 | ((int)in[3] & 0x3F) << 12 | ((int)in[4] & 0x3F) << 6 | ((int)in[5] & 0x3F);
        in += 6;
    } else {
        *chr = (int)in[0];
        in += 1;
    }
    return in;
}