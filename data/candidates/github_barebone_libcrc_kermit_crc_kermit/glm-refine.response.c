uint16_t __cdecl crc_kermit(const uint8_t *input_str, size_t num_bytes)
{
    uint16_t crc = 0;

    if (!crc_tab_init)
        init_crc_tab();

    for (size_t i = 0; i < num_bytes; ++i)
    {
        uint8_t index = (uint8_t)(input_str[i] ^ (crc & 0xFF));
        crc = (crc >> 8) ^ crc_tab[index];
    }

    // Swap bytes to match Kermit CRC specification
    return (crc << 8) | (crc >> 8);
}