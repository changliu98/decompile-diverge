void _itoa_hex(uint32_t val, char *buf)
{
    static const char *digits = "0123456789ABCD";
    unsigned int i;

    for (i = 0; i < 8; i++) {
        buf[7 - i] = digits[val & 0xF];
        val >>= 4;
    }
}