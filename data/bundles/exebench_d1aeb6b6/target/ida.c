void __cdecl bitmap_clear(unsigned __int64 *map, int start, int nr)
{
  __int64 v3; // [rsp+0h] [rbp-38h]
  unsigned __int64 mask_to_clear; // [rsp+10h] [rbp-28h]
  int bits_to_clear; // [rsp+18h] [rbp-20h]
  int size; // [rsp+1Ch] [rbp-1Ch]
  unsigned __int64 *p; // [rsp+20h] [rbp-18h]
  int nra; // [rsp+28h] [rbp-10h]

  nra = nr;
  p = &map[start / 64];
  size = nr + start;
  bits_to_clear = 64 - start % 64;
  mask_to_clear = -1LL << (start % 64);
  while ( nra - bits_to_clear >= 0 )
  {
    *p &= ~mask_to_clear;
    nra -= bits_to_clear;
    bits_to_clear = 64;
    mask_to_clear = -1LL;
    ++p;
  }
  if ( nra )
  {
    if ( size % 64 )
      v3 = (1LL << (size % 64)) - 1;
    else
      v3 = -1LL;
    *p &= ~(mask_to_clear & v3);
  }
}