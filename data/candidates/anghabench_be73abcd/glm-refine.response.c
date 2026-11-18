int __cdecl val_seg(int val)
{
    int r = 0;
    int vala = val >> 7;

    // Check if the upper 4 bits of the 7-bit shifted value are non-zero
    if (((val >> 7) & 0xF0) != 0)
    {
        vala = val >> 11;
        r = 4;
    }

    // Check if the upper 2 bits of the current vala are non-zero
    if ((vala & 0xC) != 0)
    {
        vala >>= 2;
        r += 2;
    }

    // Check if the highest remaining bit is non-zero
    if ((vala & 2) != 0)
    {
        ++r;
    }

    return r;
}