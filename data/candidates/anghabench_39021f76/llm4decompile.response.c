int all_bits_clear(uint32_t test, uint32_t mask)
{
 return (test & mask) == 0;
}