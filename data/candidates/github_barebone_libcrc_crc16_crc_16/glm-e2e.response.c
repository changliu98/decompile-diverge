uint16_t crc_16(const unsigned char *input_str, size_t num_bytes) {
    uint16_t crc = 0;
    const unsigned char *ptr = input_str;

    if (ptr == NULL) {
        return 0;
    }

    if (!(crc_tab16_init & 1)) {
        init_crc16_tab();
    }

    for (size_t a = 0; a < num_bytes; a++) {
        crc = (crc >> 8) ^ crc_tab16[(crc ^ *ptr++) & 0xFF];
    }

    return crc;
}