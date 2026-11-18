unsigned int __cdecl gf32_mod(unsigned __int64 r, int high_bit)
{
  while ( high_bit >= 32 )
  {
    if ( (r & (1LL << high_bit)) != 0 )
      r ^= 517762881LL << ((unsigned __int8)high_bit - 32);
    --high_bit;
  }
  return r;
}