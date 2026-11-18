void bToHex0(char *out, unsigned char val) {
    static const char hex_chars[] = "0123456789abcdef";
    
    out[0] = hex_chars[(val >> 4) & 0xF];
    out[1] = hex_chars[val & 0xF];
    out[2] = '\0';
}