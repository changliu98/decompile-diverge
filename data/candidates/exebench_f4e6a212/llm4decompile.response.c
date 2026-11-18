void mix_16h_to_32_s2(int *dest, short *src, int count)
{
    int i;
    int *dest_ptr = dest;
    short *src_ptr = src;

    count >>= 1;

    for (i = count; i != 0; i--)
    {
        *dest_ptr++ += (*src_ptr++) >> 1;
        *dest_ptr++ += (*src_ptr++) >> 1;
        src_ptr += 2;
    }
}