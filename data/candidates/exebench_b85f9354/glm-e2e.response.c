void calculate_crc(char *crc, char data) {
    *crc ^= data;
}