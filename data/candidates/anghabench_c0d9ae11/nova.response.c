int check_crc_flex(unsigned char *data, int size) {
    unsigned short crc = 0xffff;
    int i;

    if (size < 4)
        return -1;

    while (size--) {
        i = ((crc >> 8) ^ *data++) & 0xFF;
        crc = (crc << 8) ^ crc_table[i];
    }

    if ((crc & 0xffff)!= 0x7070)
        return -1;

    return 0;
}