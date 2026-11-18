void __cdecl bitmap_set(unsigned __int64 *map, int start, int nr)
{
  __int64 v3; // [rsp+0h] [rbp-38h]
  unsigned __int64 mask_to_set; // [rsp+10h] [rbp-28h]
  int bits_to_set; // [rsp+18h] [rbp-20h]
  int size; // [rsp+1Ch] [rbp-1Ch]
  unsigned __int64 *p; // [rsp+20h] [rbp-18h]
  int nra; // [rsp+28h] [rbp-10h]

  nra = nr;
  p = &map[start / 64];
  size = nr + start;
  bits_to_set = 64 - start % 64;
  mask_to_set = -1LL << (start % 64);
  while ( nra - bits_to_set >= 0 )
  {
    *p |= mask_to_set;
    nra -= bits_to_set;
    bits_to_set = 64;
    mask_to_set = -1LL;
    ++p;
  }
  if ( nra )
  {
    if ( size % 64 )
      v3 = (1LL << (size % 64)) - 1;
    else
      v3 = -1LL;
    *p |= mask_to_set & v3;
  }
}