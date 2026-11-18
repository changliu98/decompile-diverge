void WordToHex(unsigned int word, char *out) {
    unsigned int shifted = word;
    int i = 3;
    
    while (i >= 0) {
        unsigned int nibble = shifted & 0xf;
        
        if (nibble < 10) {
            out[i] = (char)(nibble + '0');
        } else {
            out[i] = (char)(nibble - 10 + 'A');
        }
        
        shifted = (shifted >> 4) & 0xfff;
        i--;
    }
    
    out[4] = '\0';
}