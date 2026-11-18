uint32_t F(uint32_t a, uint32_t b, uint32_t c)
{
    // Compute the bitwise function F(x, y, z) = (x AND y) OR ((NOT x) AND z)
    // This is equivalent to the conditional selection: if x then y else z
    return a & b | (a ^ 0xffffffff) & c;
}