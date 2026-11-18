void sync_clear_bit(int bit_index, unsigned_long *bitmap_ptr)
{
    LOCK(); // Acquire lock to ensure atomic operation
    // Clear the bit at position 'nr' in the address pointed to by 'addr'
    // nr >> 3 calculates the byte index (nr / 8)
    // nr & 7 calculates the bit offset within the byte (nr % 8)
    // ~((unsigned_long)1 << (nr & 7)) creates a mask with all bits set except the bit at position (nr & 7)
    // The bitwise AND operation clears the specific bit
    bitmap_ptr[bit_index >> 3] &= ~((unsigned_long)1 << (bit_index & 7));
    UNLOCK(); // Release lock
}