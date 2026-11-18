/**
 * Toggles the bit at position 'nr' in the memory location pointed to by 'addr'.
 *
 * @param nr   The bit index to toggle (0-based).
 * @param addr Pointer to an array of unsigned long integers representing the bit array.
 */
void change_bit(int bit_index, unsigned_long *bit_array)
{
    // Calculate the index of the unsigned long word containing the bit.
    // Each word holds 0x40 (64) bits.
    unsigned long word_idx = bit_index / 0x40;

    // Calculate the bit position within the word.
    // Use modulo 0x40 to get the offset, cast to byte and mask with 0x3f to ensure
    // the shift amount is within the valid range [0, 63].
    unsigned long bit_pos = ((byte)((long)bit_index % 0x40) & 0x3f);

    // Create a mask with a single bit set at the calculated offset.
    unsigned long mask = 1L << bit_pos;

    // Toggle the bit at the calculated position using XOR.
    bit_array[word_idx] ^= mask;
}