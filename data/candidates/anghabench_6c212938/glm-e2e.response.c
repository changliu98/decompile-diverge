void copy_le16(unsigned char *buf, unsigned short val) {
    buf[0] = val & 0xff;
    buf[1] = (val >> 8) & 0xff;
}