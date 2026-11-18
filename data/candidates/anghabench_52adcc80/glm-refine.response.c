uint16_t __cdecl BigUnsignedShort(uint16_t value)
{
    return (value >> 8) | (value << 8);
}