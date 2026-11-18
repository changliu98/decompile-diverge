int __cdecl byte_col_big5(int byte)
{
    // Valid range 1: 0x40 ('@') to 0x7E ('~')
    if (byte >= 0x40 && byte < 0x7F)
        return byte - 64; // 0x40 - 64 = 0

    // Valid range 2: 0xA1 to 0xFE
    if (byte >= 0xA1 && byte < 0xFF)
        return byte - 98; // 0xA1 - 98 = 63

    // Invalid byte
    return -1;
}