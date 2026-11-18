unsigned int __cdecl and_peep2_q(unsigned int y, unsigned int *x)
{
  *x = y & 0xFE;
  return y;
}