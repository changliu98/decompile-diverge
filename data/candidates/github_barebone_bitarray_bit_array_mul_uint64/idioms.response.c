void bit_array_mul_uint64(struct bit_array *array, unsigned long multiplier)
{
  if (array->num_of_bits == 0 || multiplier == 1)
    return;
  if (multiplier == 0)
    bit_array_clear(array);
  else
  {
    for (bit_index_t i = array->num_of_bits; i > 0; i--)
    {
      if (array->words[(i - 1) / (sizeof(bit_word) * 8)] & (1UL << ((i - 1) % (sizeof(bit_word) * 8))))
      {
        array->words[(i - 1) / (sizeof(bit_word) * 8)] &= ~(1UL << ((i - 1) % (sizeof(bit_word) * 8)));
        bit_array_set(array, i - 1, multiplier);
      }
    }
  }
}