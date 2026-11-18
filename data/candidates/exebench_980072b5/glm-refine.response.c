void __cdecl set_bit(int nr, volatile unsigned __int64 *addr)
{
    // Calculate the 64-bit word index and the bit position within that word
    int word_index = nr / 64;
    int bit_pos = nr % 64;

    // Set the specific bit using a bitwise OR operation
    addr[word_index] |= (1ULL << bit_pos);
}