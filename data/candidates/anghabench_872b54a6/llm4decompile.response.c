int byte_row_johab_hangul(int byte)
{
    if (byte >= 0x84 && byte <= 0xd3)
        return byte - 0x84;
    else
        return -1;
}