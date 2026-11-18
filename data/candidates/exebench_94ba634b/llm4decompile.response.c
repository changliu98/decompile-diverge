void _jis_shift(uint8_t *y, uint8_t *x)
{
    uint8_t tmp = *y;
    uint8_t rowOffset = (tmp >= 95) ? 18*2 : 14*2;
    uint8_t cellOffset = (tmp % 2) ?
        ((*x >= 96) ? 32 : 31) :
        126;

    *y = rowOffset + ((tmp + 1) >> 1);
    *x += cellOffset;
}