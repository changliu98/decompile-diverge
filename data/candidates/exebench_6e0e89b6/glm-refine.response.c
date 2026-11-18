void __cdecl clear_bit(int nr, unsigned __int64 *addr)
{
    // 1. Find the 64-bit word containing the target bit.
    //    Equivalent to: nr / 64
    unsigned __int64 word_index = (unsigned __int64)nr >> 6;

    // 2. Find the bit's offset within that 64-bit word.
    //    Equivalent to: nr % 64
    unsigned __int64 bit_offset = nr & 0x3F;

    // 3. Create a mask with the target bit set to 0, and all others set to 1.
    //    Equivalent to: ~(1ULL << bit_offset)
    unsigned __int64 mask = ~(1LL << bit_offset);

    // 4. Apply the mask to clear the bit using bitwise AND.
    addr[word_index] &= mask;
}