void poly1305_add(unsigned char *dst, const unsigned char *src) {
    unsigned short carry = 0;
    for (unsigned int i = 0; i < 18; i++) {
        unsigned short sum = (unsigned short)dst[i] + (unsigned short)src[i] + carry;
        dst[i] = (unsigned char)(sum & 0xff);
        carry = sum >> 8;
    }
}