static inline unsigned short BigUnsignedShort(unsigned short x)
{
    return ( ((x & (unsigned short) 0x00ffU) << 8) |
             ((x & (unsigned short) 0xff00U) >> 8) );
}