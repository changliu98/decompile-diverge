void decode_mode10_short_delta(int delta, int *dr, int *dg, int *db)
{
  *db = delta & 0x1f;
  if ( *db & 0x10 )
    *db |= 0xf0;
  *db = *db * 2;
  *dg = (delta & 0x3e0) >> 5;
  if ( *dg & 0x10 )
    *dg |= 0xf0;
  *dr = (delta & 0x7c00) >> 10;
  if ( *dr & 0x10 )
    *dr |= 0xf0;
}