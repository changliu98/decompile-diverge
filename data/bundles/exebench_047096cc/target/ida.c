void __cdecl endian_swap32bit(unsigned int *x)
{
  *x = (*x << 24) | (*x >> 8) & 0xFF00 | (*x << 8) & 0xFF0000 | ((unsigned __int64)*x >> 24);
}