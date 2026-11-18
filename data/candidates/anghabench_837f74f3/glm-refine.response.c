void __cdecl set_bit(uint8_t *data, size_t pos)
{
    size_t byte_index = pos / 8;
    size_t bit_index  = pos % 8;
    uint8_t mask = 1 << (7 - bit_index);
    
    data[byte_index] |= mask;
}