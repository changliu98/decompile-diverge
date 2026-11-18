static void decode_mode10_short_delta(int delta, int *dr, int *dg, int *db)
{
  *db = (delta & 0x001f);
  if (*db & 0x10) *db |= ~((int)0x0f);
  *db <<= 1;

  *dg = (delta & 0x03e0) >> 5;
  if (*dg & 0x10) *dg |= ~((int)0x0f);

  *dr = (delta & 0x7c00) >> 10;
  if (*dr & 0x10) *dr |= ~((int)0x0f);
}