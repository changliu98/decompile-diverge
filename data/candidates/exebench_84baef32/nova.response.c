static void _itoa_hex(unsigned int value, char *result) {
    static const char hex_chars[] = "0123456789ABCDEF";
    unsigned int index = 0;

    while (index < 8) {
        result[7 - index] = hex_chars[value & 0xF];
        value >>= 4;
        ++index;
    }
}