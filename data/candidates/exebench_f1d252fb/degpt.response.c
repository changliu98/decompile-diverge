/**
 * Swaps the byte order of a 16-bit unsigned integer.
 * 
 * @param x Pointer to the 16-bit unsigned integer to be byte-swapped.
 */
void endian_swap16bit(unsigned_short *value)
{
    // Shift the lower byte to the upper position and the upper byte to the lower position
    // to achieve byte-order swapping (endianness conversion).
    *value = *value >> 8 | *value << 8;
}