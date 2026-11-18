void __cdecl crc8_byte(uint8_t *crc, uint8_t data)
{
    for (int i = 0; i < 8; ++i)
    {
        // Check if the LSB of the XOR between data and crc is 1
        uint8_t bit = (data ^ *crc) & 1;
        
        // Shift both bytes right by 1
        *crc >>= 1;
        data >>= 1;
        
        // If the extracted bit was 1, apply the polynomial
        if (bit)
        {
            *crc ^= 0x8C;
        }
    }
}