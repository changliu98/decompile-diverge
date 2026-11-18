void __cdecl change_bit(int nr, volatile unsigned __int64 *addr)
{
    // Calculate the 64-bit word index and the bit position within that word
    int word_idx = nr / 64;
    int bit_pos = nr % 64;
    
    // Toggle the specific bit using XOR
    addr[word_idx] ^= 1ULL << bit_pos;
}