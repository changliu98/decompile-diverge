void __cdecl edosk2674_smsc_outw(uint16_t value, volatile uint16_t *addr)
{
    // Swap the high and low bytes of the 16-bit value before writing
    *addr = (value << 8) | (value >> 8);
}