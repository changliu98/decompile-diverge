void copy_le16(unsigned char *dest, unsigned int n) {
    *(unsigned short *)dest = n;
}