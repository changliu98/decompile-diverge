unsigned char fdc_crc4(unsigned char *buffer, size_t len)
{
    unsigned char crc = 0x0F;
    int shift;
    size_t i;

    for (i = 0; i < len; i++) {
        for (shift = 7; shift > 0; shift--) {
            crc <<= 1;
            if (buffer[i] & (1 << shift)) {
                crc |= 1;
            }
            if (crc & 0x10) {
                crc ^= 0x03;
            }
        }
    }
    return crc & 0x0F;
}