void gsm_hex_from_byte(char *out, int value) {
    static const char hexdigits[] = "0123456789abcdef";
    
    out[0] = hexdigits[(value >> 4) & 0xF];
    out[1] = hexdigits[value & 0xF];
}