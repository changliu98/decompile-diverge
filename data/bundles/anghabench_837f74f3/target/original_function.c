void set_bit(uint8_t* data, size_t pos)
{
    uint8_t mask = 1 << 7-(pos%8);
    data[pos/8] |= mask;
}