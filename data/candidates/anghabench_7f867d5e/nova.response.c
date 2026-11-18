uint8_t gfmul(uint8_t crc, uint8_t byte, uint8_t poly) {
    uint8_t i, b;
    for (i = 0; i < 8; i++) {
        b = byte & 0x80;
        if (b) {
            crc ^= poly;
        }
        byte <<= 1;
        if (b) {
            byte ^= (1 << 29);
        }
    }
    return crc;
}