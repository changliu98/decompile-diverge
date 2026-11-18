/**
 * Sets the bit at position 'nr' in the memory location pointed to by 'addr'.
 *
 * @param nr   The bit number to set (0-indexed).
 * @param addr Pointer to the memory address where the bit should be set.
 */
void set_bit(int bit_index, unsigned_long *address)
{
    // Calculate the byte address containing the bit by adding the byte offset (nr / 8) to the base address.
    byte *byte_ptr = (byte *)((long)address + ((long)bit_index >> 3));
    
    // Set the specific bit within the byte using bitwise OR.
    // (nr & 7U) computes the bit position within the byte (nr % 8).
    // '\x01' << (nr & 7U) creates a mask with only that bit set.
    *byte_ptr = *byte_ptr | '\x01' << (bit_index & 7U);
}