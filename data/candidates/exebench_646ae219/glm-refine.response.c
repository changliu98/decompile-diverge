void __cdecl clear_bit(int nr, volatile unsigned __int64 *addr)
{
    // Calculate the 64-bit word index and the bit position within that word
    int word_index = nr / 64;
    int bit_pos = nr % 64;

    // Create a mask with a 1 at the target bit position, then invert it
    unsigned __int64 mask = ~(1ULL << bit_pos);

    // Atomically (or volatile-ly) clear the bit using bitwise AND
    addr[word_index] &= mask;
}