void __cdecl dpaa_clear_bits(unsigned __int64 mask, volatile unsigned __int64 *p)
{
  *p &= ~mask;
}