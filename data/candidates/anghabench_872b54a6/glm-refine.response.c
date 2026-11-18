define JOHAB_HANGUL_BYTE_OFFSET 132

int __cdecl byte_row_johab_hangul(int byte)
{
    // Check if the byte falls outside the valid Hangul range
    if (byte < JOHAB_HANGUL_BYTE_OFFSET || byte >= 212)
        return -1;
    
    // Map the byte to its corresponding row index
    return byte - JOHAB_HANGUL_BYTE_OFFSET;
}