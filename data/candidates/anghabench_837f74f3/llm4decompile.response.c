void set_bit(unsigned char *data, size_t pos)
{
    unsigned char mask = 1 << 7-(pos%8);
    data[pos/8] |= mask;
}