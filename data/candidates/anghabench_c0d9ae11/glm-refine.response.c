int check_crc_flex(const uint8_t *data, int size)
{
    uint16_t crc = 0xFFFF;

    if (size < 3)
        return -1;

    while (size--)
    {
        uint8_t index = *data++ ^ (crc >> 8);
        crc = (crc << 8) ^ crc_flex_table[index];
    }

    if (crc == 0x7047)
        return 0;
    else
        return -1;
}