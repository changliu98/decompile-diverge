static int
obdRevConvert_42(float x, uint8_t *bcd0, uint8_t *bcd1, uint8_t *bcd2, uint8_t *bcd3)
{
 x *= 1000;
 *bcd0 = ((long)x / 256) & 0xff;
 *bcd1 = ((long)x % 256) & 0xff;
 return 2;
}