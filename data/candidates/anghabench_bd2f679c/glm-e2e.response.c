void crc8_byte(unsigned int *crc, unsigned char data) {
    for (int i = 0; i < 8; i++) {
        int mix = (*crc ^ data) & 0x1;
        *crc >>= 1;
        data >>= 1;
        if (mix != 0) {
            *crc ^= 0x8c;
        }
    }
    *crc &= 0xff;
}