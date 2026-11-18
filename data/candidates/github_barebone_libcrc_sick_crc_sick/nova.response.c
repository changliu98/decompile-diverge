static uint16_t crc_sick(const char *data, size_t size) {
    uint16_t crc = 0;
    size_t i = 0;
    while (data && i < size) {
        uint8_t byte = (uint8_t)*data;
        uint16_t x = (crc & 0x8000)? (crc << 1) ^ 0x1021 : (crc << 1);
        crc = crc ^ (byte << 8);
        crc = crc & 0xFFFF;
        data++;
        i++;
    }
    uint8_t lo = crc & 0xFF;
    uint8_t hi = (crc & 0xFF00) >> 8;
    crc = (lo << 8) | hi;
    return crc;
}