void byteReverse(unsigned int *x)
{
    x[0] = (((x[0]) & 0xff000000) >> 24) | (((x[0]) & 0x00ff0000) >> 8) | (((x[0]) & 0x0000ff00) << 8) | (((x[0]) & 0x000000ff) << 24);
}