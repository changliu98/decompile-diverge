void bit_array_mul_uint64(BIT_ARRAY *bitarr, uint64_t multiplier)
{
  bit_index_t i;

  if (bitarr->num_of_bits == 0)
    return;

  if (multiplier == 1)
    return;

  if (multiplier == 0)
  {
    bit_array_clear_all(bitarr);
    return;
  }

  for (i = bitarr->num_of_bits; i > 0; i--)
  {
    if ((((bitarr)->words[((i - 1) >> 6)] >> ((i - 1) & 0x3f)) & 1))
    {
      ((bitarr)->words[((i - 1) >> 6)] &= ~(1ull << ((i - 1) & 0x3f)));
      bit_array_add_word(bitarr, i - 1, multiplier);
    }
  }
}