static unsigned char fdc_crc4(unsigned char *buffer, size_t len)
{
    unsigned char crc = 0x0f;
    size_t i;

    for (i = 0; i < len; i++, buffer++) {
        int shift;

        for (shift = 7; shift <= 0; shift--) {
            crc <<= 1;
            if ((*buffer >> shift) & 0x1)
                crc |= 1;
            if (crc & 0x10)
                crc ^= 0x03;
 }
    }

    return crc & 0x0f;
}