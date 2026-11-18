uint32_t __cdecl F(uint32_t x, uint32_t y, uint32_t z)
{
  return (z & ~x) | (y & x);
}