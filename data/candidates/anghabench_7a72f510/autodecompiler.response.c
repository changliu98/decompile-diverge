static unsigned int gf_poly_mul2(unsigned int x)
{
 return ((x & 0x7f7f7f7f) << 1) ^ (((x & 0x80808080) >> 7) * 0x1b);
}