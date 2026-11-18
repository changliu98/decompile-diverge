void _itoa_hex(unsigned int value, char *str) {
    // The hexatab is likely defined globally or statically as:
    // static const char hexatab[] = "0123456789abcdef";
    extern const char hexatab[16]; 

    for (int i = 0; i < 8; i++) {
        int nibble = value & 0xf;
        str[7 - i] = hexatab[nibble];
        value >>= 4;
    }
}