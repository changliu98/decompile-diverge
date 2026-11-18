/*
 * Set the bit at position 'nr' in the bitmap pointed to by 'addr'.
 *
 * Parameters:
 *   nr   - The bit number to set (0-indexed).
 *   addr - Pointer to the unsigned long array representing the bitmap.
 *
 * Implementation:
 *   - nr >> 6 is equivalent to nr / 64, determining the index of the unsigned long
 *     word in the array that contains the bit.
 *   - nr & 0x3f is equivalent to nr % 64, determining the bit position within that word.
 *   - 1L << (nr & 0x3f) creates a mask with only the target bit set.
 *   - The |= operator sets the target bit in the specified word without affecting other bits.
 */
void set_bit(int bit_index, unsigned_long *bitmap)
{
    bitmap[bit_index >> 6] |= 1L << (bit_index & 0x3f);
}