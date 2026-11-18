void __cdecl decode_mode10_short_delta(int delta, int *dr, int *dg, int *db)
{
  *db = delta & 0x1F;
  if ( (*db & 0x10) != 0 )
    *db |= 0xFFFFFFF0;
  *db *= 2;
  *dg = (delta & 0x3E0) >> 5;
  if ( (*dg & 0x10) != 0 )
    *dg |= 0xFFFFFFF0;
  *dr = (delta & 0x7C00) >> 10;
  if ( (*dr & 0x10) != 0 )
    *dr |= 0xFFFFFFF0;
}