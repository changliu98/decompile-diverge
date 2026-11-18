void _sjis_shift(uint8_t *p1, uint8_t *p2)
{
    uint8_t adjust = *p2 < 159;
    uint8_t rowOffset = *p1 < 160 ? 112 : 176;
    uint8_t cellOffset = adjust ? ( *p2 < 128 ? 126 : 32 ) : 31;

    *p1 = ((*p1 % rowOffset) << 1) - adjust;
    *p2 -= cellOffset;
}