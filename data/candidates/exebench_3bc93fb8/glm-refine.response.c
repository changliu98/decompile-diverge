void __cdecl bitmap_set(unsigned __int64 *map, int start, int nr)
{
    unsigned __int64 *p = &map[start / 64];
    int end = start + nr;
    int bits_to_set = 64 - (start % 64);
    
    // Mask for the first chunk (sets bits from 'start' to the end of the 64-bit word)
    unsigned __int64 mask_to_set = ~0ULL << (start % 64);

    // Loop while we have enough bits to fill the remainder of the current word
    while (nr >= bits_to_set)
    {
        *p |= mask_to_set;
        nr -= bits_to_set;
        
        // For subsequent words, we attempt to set all 64 bits
        bits_to_set = 64;
        mask_to_set = ~0ULL;
        ++p;
    }

    // Handle the remaining bits in the final partially-covered word
    if (nr > 0)
    {
        unsigned __int64 tail_mask;
        int end_offset = end % 64;
        
        // Mask for the tail (sets bits from the start of the word up to 'end')
        if (end_offset == 0)
            tail_mask = ~0ULL;
        else
            tail_mask = (1ULL << end_offset) - 1;

        *p |= mask_to_set & tail_mask;
    }
}