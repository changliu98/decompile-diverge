void __cdecl endian_swap16bit(unsigned __int16 *x)
{
  *x = (*x << 8) | ((int)*x >> 8);
}