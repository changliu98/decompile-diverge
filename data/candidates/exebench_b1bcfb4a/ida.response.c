void __cdecl dpaa_set_bits(unsigned __int64 mask, volatile unsigned __int64 *p)
{
  *p |= mask;
}