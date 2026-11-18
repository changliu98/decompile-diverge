int __cdecl all_bits_clear(unsigned int test, unsigned int mask)
{
  return (mask & test) == 0;
}