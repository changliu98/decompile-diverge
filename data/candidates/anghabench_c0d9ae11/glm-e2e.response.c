int check_crc_flex(const uint8_t *data, int length) {
    uint16_t crc = 0xFFFF;
    int ret;

    if (length < 3) {
        ret = -1;
    } else {
        while (length != 0) {
            length--;
            uint8_t byte = *data++;
            crc = (crc << 8) ^ crc_flex_table[(crc >> 8 ^ byte) & 0xFF];
        }

        if ((crc & 0xFFFF) == 0x7070) {
            ret = 0;
        } else {
            ret = -1;
        }
    }

    return ret;
}