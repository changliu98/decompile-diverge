void set_bit(int bit_number, unsigned long long *bitmap)
{
    int word_index = bit_number / 64;
    int bit_offset = bit_number % 64;
    
    bitmap[word_index] |= (1ULL << bit_offset);
}