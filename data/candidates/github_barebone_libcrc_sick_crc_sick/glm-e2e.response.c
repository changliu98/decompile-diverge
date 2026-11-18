uint16_t crc_sick(const uint8_t *data, uint64_t len) {
    uint16_t crc = 0;
    const uint8_t *ptr = data;
    uint16_t prev = 0;

    if (ptr == NULL) {
        return 0;
    }

    for (uint64_t i = 0; i < len; i++) {
        uint16_t cur = *ptr & 0xFF;

        if (crc & 0x8000) {
            crc = (crc << 1) ^ 0x8005;
        } else {
            crc = crc << 1;
        }

        crc ^= cur | prev;
        prev = cur << 8;
        
        ptr++;
    }

    uint16_t high = (crc & 0xFF00) >> 8;
    uint16_t low = (crc & 0xFF) << 8;
    
    crc = high | low;

    return crc;
}