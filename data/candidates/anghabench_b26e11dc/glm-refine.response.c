unsigned int __cdecl _sw_hweight16(unsigned int w)
{
    unsigned int x = w - ((w >> 1) & 0x5555);
    unsigned int y = (x & 0x3333) + ((x >> 2) & 0x3333);
    unsigned int z = y + (y >> 4);
    
    return (z & 0x0F0F) + ((z >> 8) & 0x0F0F);
}