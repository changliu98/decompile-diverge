unsigned short crc_kermit( unsigned char *pcBlock, unsigned long ulLen )
{
    unsigned long i;
    unsigned short crc;
    unsigned short low_byte, high_byte;

    if (!(crc_tab_init & 2))
        init_crc_tab();

    crc = 0;

    if (pcBlock != NULL) {
        for (i = 0; i < ulLen; i++) {
            crc = (crc >> 8) ^ crc_kermit_tab[(crc & 0xFF) ^ *pcBlock++];
        }
    }

    low_byte = (crc & 0xFF00) >> 8;
    high_byte = (crc & 0xFF) << 8;
    crc = low_byte | high_byte;

    return crc;
}