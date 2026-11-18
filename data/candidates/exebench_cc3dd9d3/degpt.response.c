void AssignBit(unsigned_long *bit_array, int target_bit, int bit_value)
{
    // Calculate the bit mask for the specific bit position within a word
    // (byte)bit & 0x3f extracts the lower 6 bits (bit index within the 64-bit word)
    unsigned_long bit_mask = 1L << ((byte)target_bit & 0x3f);
    
    // Determine the index of the word in the array that contains the target bit
    // bit >> 6 is equivalent to bit / 64, finding which 64-bit word holds the bit
    unsigned_long *target_word = &bit_array[target_bit >> 6];
    
    if (bit_value == 0) {
        // Clear the bit by ANDing with the complement of the mask
        *target_word &= ~bit_mask;
    } else {
        // Set the bit by ORing with the mask
        *target_word |= bit_mask;
    }
}