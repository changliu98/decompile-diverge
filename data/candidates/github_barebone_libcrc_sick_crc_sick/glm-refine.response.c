uint16_t __cdecl crc_sick(const uint8_t *input_str, size_t num_bytes)
{
    size_t i;
    const uint8_t *ptr;
    uint16_t prev_byte;
    uint16_t cur_byte;
    uint16_t crc;
    uint16_t shifted_crc;

    crc = 0;
    ptr = input_str;
    prev_byte = 0;

    if (input_str)
    {
        for (i = 0; i < num_bytes; ++i)
        {
            cur_byte = *ptr;
            
            if ((crc & 0x8000) != 0)
                shifted_crc = (crc << 1) ^ 0x8005;
            else
                shifted_crc = crc << 1;

            crc = (prev_byte | cur_byte) ^ shifted_crc;
            prev_byte = cur_byte << 8;
            
            ++ptr;
        }
    }
    
    // Swap the high and low bytes of the CRC before returning
    return (uint16_t)((crc << 8) | (crc >> 8));
}