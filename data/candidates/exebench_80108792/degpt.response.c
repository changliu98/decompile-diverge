void bitmap_free(uint *bitmap, int bit_index)
{
    // Clear the bit at the specified index in the bitmap array.
    // Calculate the word index by dividing the bit index by 32 (0x20).
    // Calculate the bit mask by shifting 0x80000000U right by (index % 32).
    // Apply the bitwise NOT to the mask and AND it with the word to clear the bit.
    bitmap[bit_index / 0x20] &= ~(0x80000000U >> (bit_index % 0x20));
}