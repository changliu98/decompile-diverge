unsigned __int64 __cdecl _reverse_ffs(unsigned __int64 word)
{
    int msb_index;
    unsigned __int64 shifted_word;

    shifted_word = word;
    msb_index = 0;

    // Check 16-bit halves
    if ((word & 0xFFFF0000) != 0)
        shifted_word = word >> 16;
    else
        msb_index = 16;

    // Check 8-bit halves
    if ((shifted_word & 0xFF00) != 0)
        shifted_word >>= 8;
    else
        msb_index += 8;

    // Check 4-bit halves
    if ((shifted_word & 0xF0) != 0)
        shifted_word >>= 4;
    else
        msb_index += 4;

    // Check 2-bit halves
    if ((shifted_word & 0xC) != 0)
        shifted_word >>= 2;
    else
        msb_index += 2;

    // Check final bit
    if ((shifted_word & 2) == 0)
        ++msb_index;

    return msb_index;
}