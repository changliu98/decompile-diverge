void __cdecl bitmap_clear(unsigned __int64 *map, int start, int nr)
{
  unsigned __int64 *p = &map[start / 64];
  int end = start + nr;
  int bits_to_clear = 64 - (start % 64);
  unsigned __int64 mask_to_clear = ~0ULL << (start % 64);

  // Clear full or partial 64-bit chunks
  while (nr >= bits_to_clear)
  {
    *p &= ~mask_to_clear;
    nr -= bits_to_clear;
    bits_to_clear = 64;
    mask_to_clear = ~0ULL;
    ++p;
  }

  // Clear the remaining bits
  if (nr)
  {
    unsigned __int64 end_mask;
    if (end % 64)
      end_mask = (1ULL << (end % 64)) - 1;
    else
      end_mask = ~0ULL;

    *p &= ~(mask_to_clear & end_mask);
  }
}