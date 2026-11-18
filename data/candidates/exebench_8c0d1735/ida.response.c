unsigned int __cdecl and_peep2_qi(unsigned int y, unsigned int *x)
{
  *x = y & 0x5F;
  return y;
}