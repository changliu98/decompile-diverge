/**
 * set_bit - Set a bit in a bitmap
 * @nr: Bit number to set
 * @addr: Address of the bitmap array
 *
 * Sets the bit at position @nr in the bitmap pointed to by @addr.
 * The bitmap is treated as an array of 64-bit unsigned long integers.
 */
void set_bit(int bit_index, unsigned_long *bitmap)
{
    // Calculate the index of the 64-bit word containing the bit
    // and set the corresponding bit within that word using bitwise OR
    bitmap[bit_index / 0x40] |= 1L << (bit_index % 0x40);
}