void crc16_b(unsigned int *crc, unsigned char data) {
    for (int i = 0; i < 8; i++) {
        *crc <<= 1;
        if (((*crc >> 16) ^ data) & 1) {
            *crc ^= 0x8005;
        }
        data >>= 1;
    }
    *crc &= 0xFFFF;
}