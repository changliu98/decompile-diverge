void clear_bit(int bit_index, unsigned_long *bitmap_ptr)
{
    // Calculate the address of the byte containing the bit to be cleared.
    // Shift nr right by 3 (equivalent to dividing by 8) to get the byte offset.
    byte *byte_ptr = (byte *)((long)bitmap_ptr + ((long)bit_index >> 3));
    
    // Clear the specific bit within that byte.
    // (nr & 7U) gets the bit position within the byte (0-7).
    // ('\x01' << (nr & 7U)) creates a mask with only that bit set.
    // ~(...) inverts the mask to have all bits set except the target bit.
    // & with *pbVar1 clears the target bit while preserving others.
    *byte_ptr = *byte_ptr & ~('\x01' << (bit_index & 7U));
}