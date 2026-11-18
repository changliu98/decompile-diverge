int render_uint32(uint32_t val, char *buf)
{
    if (val == 0) {
        buf[0] = '0';
        return 1;
    }

    int len = 0;
    while (val > 0) {
        buf[len] = "0123456789ABCDEF"[val & 0xF];
        val >>= 4;
        len++;
    }

    return len;
}