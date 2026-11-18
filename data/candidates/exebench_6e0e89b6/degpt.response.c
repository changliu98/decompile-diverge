/**
 * clear_bit - Clear a specific bit in a memory address.
 * @nr: Bit number to clear.
 * @addr: Pointer to the memory address containing the bits.
 *
 * This function clears the bit specified by @nr in the memory location
 * pointed to by @addr. It uses bitwise operations to achieve this:
 * 1. Shifts the bit number right by 6 to determine the index in the array.
 * 2. Masks the bit number with 0x3f to determine the bit position within the word.
 * 3. Clears the bit by ANDing the word with the inverse of the shifted 1UL.
 */
void clear_bit(int bit_index, unsigned_long *memory_ptr)
{
    // Calculate the index in the array by shifting nr right by 6 (equivalent to dividing by 64).
    // Create a mask with the bit at position (nr & 0x3f) set to 1, then invert it.
    // AND the word at the calculated index with the inverted mask to clear the bit.
    memory_ptr[bit_index >> 6] &= ~(1UL << (bit_index & 0x3f));
}