void bit_array_mul_uint64(BIT_ARRAY *bitarr, uint64_t multiplier)
{
  if(bitarr->num_of_bits == 0 || multiplier == 1)
  {
    return;
  }
  else if(multiplier == 0)
  {
    bit_array_clear_all(bitarr);
    return;
  }

  bit_index_t i;

  for(i = bitarr->num_of_bits; i > 0; i--)
  {
    if(bit_array_get(bitarr, i-1))
    {
      bit_array_clear(bitarr, i-1);
      bit_array_add_word(bitarr, i-1, multiplier);
    }
  }

  DEBUG_VALIDATE(bitarr);
}