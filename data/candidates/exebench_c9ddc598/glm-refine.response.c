void __cdecl bitmap_set(unsigned __int64 *map, int start, int nr)
{
    unsigned __int64 *p = &map[start / 64];
    int end = start + nr;
    int bits_to_set = 64 - (start % 64);
    unsigned __int64 mask = ~0ULL << (start % 64);
    int nra = nr;

    // Set bits in fully covered 64-bit chunks
    while (nra >= bits_to_set)
    {
        *p |= mask;
        nra -= bits_to_set;
        bits_to_set = 64;
        mask = ~0ULL;
        ++p;
    }

    // Set bits in the final partially covered chunk
    if (nra)
    {
        unsigned __int64 tail_mask;
        if (end % 64)
            tail_mask = (1ULL << (end % 64)) - 1;
        else
            tail_mask = ~0ULL;

        *p |= mask & tail_mask;
    }
}