void unpackFloat(float f, int *exponent, int *magnitude)
{
    *exponent = ((int)((f) & 0x7F800000) >> 23) - 127;
    *magnitude = ((int)((f) & 0x007FFFFF) | 0x00800000);
    if (((int)((f) & 0x80000000) >> 31))
        *magnitude = -*magnitude;
}