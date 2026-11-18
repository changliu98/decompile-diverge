int render_uint32(uint32_t val, char *buf) {
    int len;
    int i = 0;

    if (val == 0) {
        buf[0] = '0';
        len = 1;
    } else {
        while (val > 0) {
            buf[i++] = hex_digits[val & 0xf];
            val >>= 4;
        }
        len = i;
    }

    return len;
}