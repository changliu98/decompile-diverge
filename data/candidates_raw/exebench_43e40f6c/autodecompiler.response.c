static int
float_to_bcd11(float x, uint8_t *bcd0, uint8_t *bcd1, uint8_t *bcd2,
               uint8_t *bcd3)
{
    x *= 4;
    *bcd0 = (uint8_t) ((long) x / 256);
    *bcd1 = (uint8_t) ((long) x % 256);
    return 2;
}