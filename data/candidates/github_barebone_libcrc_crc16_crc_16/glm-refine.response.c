uint16_t __cdecl crc_16(const unsigned __int8 *input_str, size_t num_bytes)
{
    uint16_t crc = 0;
    const unsigned __int8 *ptr = input_str;

    // Initialize the CRC lookup table if it hasn't been already
    if ((crc_tab16_init & 1) == 0)
        init_crc16_tab();

    if (input_str)
    {
        for (size_t i = 0; i < num_bytes; ++i)
        {
            uint8_t byte = *ptr++;
            crc = crc_tab16[(uint8_t)(byte ^ crc)] ^ (crc >> 8);
        }
    }

    return crc;
}