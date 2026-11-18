void __cdecl endian_swap16bit(unsigned __int16 *x)
{
    *x = (*x << 8) | (*x >> 8);
}