unsigned int fons__decutf8(unsigned int *state, unsigned int *codep, unsigned int byte) {
    unsigned char type = fons__decutf8_utf8d[byte];
    unsigned int cp;

    if (*state == FONS_UTF8_ACCEPT) {
        cp = (0xFF >> type) & byte;
    } else {
        cp = (*codep << 6) | (byte & 0x3F);
    }

    *codep = cp;
    *state = fons__decutf8_utf8d[0x100 + *state + type];
    
    return *state;
}