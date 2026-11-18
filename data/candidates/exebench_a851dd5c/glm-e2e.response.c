uint8_t fdc_crc4(const uint8_t *data, size_t len) {
    uint8_t crc = 0xF;
    
    for (size_t i = 0; i < len; i++) {
        for (int bit = 7; bit >= 0; bit--) {
            crc <<= 1;
            
            if ((data[i] >> bit) & 1) {
                crc |= 1;
            }
            
            if (crc & 0x10) {
                crc ^= 0x3;
            }
        }
    }
    
    return crc & 0xF;
}