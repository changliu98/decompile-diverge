void bitfield_set(uint64_t *bitfield, int bit_index) {
    int word_index = bit_index >> 6; // Equivalent to bit_index / 64
    int bit_offset = bit_index & 0x3f; // Equivalent to bit_index % 64
    
    // Set the specific bit in the 64-bit word
    bitfield[word_index] |= (1ULL << bit_offset);
}