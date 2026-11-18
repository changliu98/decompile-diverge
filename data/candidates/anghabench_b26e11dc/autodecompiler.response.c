int __sw_hweight16(unsigned int v)
{
    unsigned int c;
    static const unsigned int B[] = {
        0x55555555,
        0x33333333,
        0x0F0F0F0F,
        0x00FF00FF,
        0x0000FFFF
    };

    c = v - ((v >> 1) & B[0]);
    c = ((c >> 2) & B[1]) + (c & B[1]);
    c = ((c >> 4) + c) & B[2];
    c = ((c >> 8) + c) & B[3];

    return c;
}