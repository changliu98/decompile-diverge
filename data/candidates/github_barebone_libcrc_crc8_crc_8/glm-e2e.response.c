unsigned char crc_8(const unsigned char *data, unsigned long len) {
    unsigned char crc = 0;
    const unsigned char *p = data;
    
    if (p != NULL) {
        for (unsigned long i = 0; i < len; i++) {
            unsigned char byte = *p++;
            crc = sht75_crc_table[byte ^ crc];
        }
    }
    
    return crc;
}