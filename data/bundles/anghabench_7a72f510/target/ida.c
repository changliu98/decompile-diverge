uint32_t __cdecl gf_poly_mul2(uint32_t x)
{
  return (27 * ((x & 0x80808080) >> 7)) ^ (2 * (x & 0x7F7F7F7F));
}