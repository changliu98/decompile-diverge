uint8_t __cdecl crc_8(const uint8_t *input_str, size_t num_bytes)
{
    uint8_t crc = 0;

    if (input_str != NULL)
    {
        for (size_t i = 0; i < num_bytes; ++i)
        {
            crc = sht75_crc_table[crc ^ input_str[i]];
        }
    }

    return crc;
}