// Calculates the row index for Johab Hangul characters.
// Returns the row index (0-75) if the byte is within the valid range (0x84-0xD3),
// otherwise returns -1.
int byte_row_johab_hangul(int input_byte)
{
    return (input_byte >= 0x84 && input_byte <= 0xd3) ? input_byte - 0x84 : -1;
}