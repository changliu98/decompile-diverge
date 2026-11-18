uint16_t crc_kermit(const unsigned char *data, uint64_t len) {
    uint16_t crc = 0;
    const unsigned char *p = data;

    if ((crc_tab_init & 1) == 0) {
        init_crc_tab();
    }

    if (p != NULL) {
        for (uint64_t i = 0; i < len; i++) {
            uint16_t idx = (crc ^ *p++) & 0xFF;
            crc = (crc >> 8) ^ crc_tab[idx];
        }
    }

    // Swap high and low bytes
    uint16_t high_byte = (crc & 0xFF00) >> 8;
    uint16_t low_byte = (crc & 0x00FF) << 8;
    crc = high_byte | low_byte;

    return crc;
}