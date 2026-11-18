int check_crc_flex(unsigned char *buf, int len)
{
    unsigned short crc = 0xffff;

    if (len < 3)
        return -1;

    while (len--)
        crc = (crc << 8) ^ crc_flex_table[(crc >> 8) ^ *buf++];

    if (crc == 0x7070)
        return 0;

    return -1;
}