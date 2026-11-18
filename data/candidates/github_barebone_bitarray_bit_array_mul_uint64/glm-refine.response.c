void __cdecl bit_array_mul_uint64(BIT_ARRAY *bitarr, uint64_t multiplier)
{
  // If the array is empty, or we are multiplying by 1, do nothing
  if (!bitarr->num_of_bits || multiplier == 1)
    return;

  if (multiplier == 0)
  {
    bit_array_clear_all(bitarr);
    return;
  }

  // Iterate through the bit array from the most significant bit down to 0
  for (bit_index_t i = bitarr->num_of_bits; i > 0; --i)
  {
    bit_index_t bit_idx = i - 1;
    int word_idx = bit_idx / 64; // Equivalent to bit_idx >> 6
    int bit_offset = bit_idx % 64; // Equivalent to bit_idx & 0x3F
    uint64_t mask = 1ULL << bit_offset;

    // If the current bit is set
    if (bitarr->words[word_idx] & mask)
    {
      // Clear the bit
      bitarr->words[word_idx] &= ~mask;
      
      // Add the multiplier at this bit's position
      bit_array_add_word(bitarr, bit_idx, multiplier);
    }
  }
}