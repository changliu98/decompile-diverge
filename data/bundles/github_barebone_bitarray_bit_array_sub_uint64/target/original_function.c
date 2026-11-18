char bit_array_sub_uint64(BIT_ARRAY* bitarr, uint64_t value)
{
  if(value == 0)
  {
    return 1;
  }
  else if(bitarr->words[0] >= value)
  {
    bitarr->words[0] -= value;
    return 1;
  }

  value -= bitarr->words[0];

  word_addr_t i;

  for(i = 1; i < bitarr->num_of_words; i++)
  {
    if(bitarr->words[i] > 0)
    {
      // deduct one
      bitarr->words[i]--;

      for(; i > 0; i--)
      {
        bitarr->words[i] = WORD_MAX;
      }

      // -1 since we've already deducted 1
      bitarr->words[0] = WORD_MAX - value - 1;

      return 1;
    }
  }

  // subtract value is greater than array
  return 0;
}