void __cdecl bitfield_set(unsigned __int64 *bits, int bit)
{
    // Calculate which 64-bit chunk the bit belongs to.
    // Shifting right by 6 is equivalent to dividing by 64.
    unsigned __int64 chunk_index = (unsigned int)bit >> 6;

    // Calculate the bit's position within that 64-bit chunk.
    // Masking with 0x3F (63) is equivalent to modulo 64.
    unsigned __int64 bit_mask = 1ULL << (bit & 0x3F);

    // Set the target bit using a bitwise OR.
    bits[chunk_index] |= bit_mask;
}