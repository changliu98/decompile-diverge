int bitcount(unsigned int v)
{
    unsigned int c;
    c = v - ((v >> 1) & 0x55555555);
    c = ((c >> 2) & 0x33333333) + (c & 0x33333333);
    c = ((c >> 4) + c) & 0x0F0F0F0F;
    c = ((c >> 8) + c);
    c = ((c >> 16) + c) & 0x000000FF;
    return c;
}