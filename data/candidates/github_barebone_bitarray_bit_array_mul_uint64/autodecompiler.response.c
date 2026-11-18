void bit_array_mul_uint64(BIT_ARRAY* bitarr, word_t multiplier)
{
  if(bitarr->num_of_bits == 0 || multiplier == 1)
  {
    return;
  }

  if(multiplier == 0)
  {
    bit_array_clear_all(bitarr);
    return;
  }

  word_addr_t i;

  for(i = bitarr->num_of_bits; i > 0; )
  {
    if(((bitarr)->words[(((i) - 1) / (sizeof(*((bitarr)->words))*8))] & (1ull << (((i) - 1) % (sizeof(*((bitarr)->words))*8)))))
    {
      ((bitarr)->words[(((i) - 1) / (sizeof(*((bitarr)->words))*8))] &= ~(1ull << (((i) - 1) % (sizeof(*((bitarr)->words))*8))));

      bit_array_add_word(bitarr, i - 1, multiplier);
    }
    else
    {
      i--;
    }
  }
}