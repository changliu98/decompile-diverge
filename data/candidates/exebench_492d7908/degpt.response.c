// Swaps the byte order of the 16-bit value 'd' and stores the result in the location pointed to by 'a'.
// This effectively performs a 16-bit endianness conversion (big-endian to little-endian or vice versa).
void edosk2674_smsc_outw(unsigned_short value, unsigned_short *output_ptr)
{
    // Shift the high byte to the low position and the low byte to the high position
    *output_ptr = value >> 8 | value << 8;
}