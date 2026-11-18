void yxyDES2_Int2Bits(uint8_t src, char *dstBits)
{
    uint8_t i;
    for (i = 0; i < 4; i++) {
        *dstBits = (src << i) & 0x08 ? 1 : 0;
        dstBits++;
    }
}