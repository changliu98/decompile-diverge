void decode_mode10_short_delta(uint16_t delta, int *dr, int *dg, int *db)
{
 *db = delta & 0x1f;
 if (*db & 0x10)
  *db |= 0xfffffff0;
 *db <<= 1;

 *dg = (delta & 0x3e0) >> 5;
 if (*dg & 0x10)
  *dg |= 0xfffffff0;

 *dr = (delta & 0x7c00) >> 10;
 if (*dr & 0x10)
  *dr |= 0xfffffff0;
}