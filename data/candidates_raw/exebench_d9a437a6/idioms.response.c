static int is_even(unsigned char *data, int len, int offset)
{
    if (data[offset] & 0x02)
        return (offset + 1);
    return (offset);
}