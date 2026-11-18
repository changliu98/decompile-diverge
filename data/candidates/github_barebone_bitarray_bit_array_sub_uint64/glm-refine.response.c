char __cdecl bit_array_sub_uint64(BIT_ARRAY *bitarr, uint64_t value)
{
  word_addr_t word_idx;
  uint64_t underflow_amount;

  if (!value)
    return 1;

  // Case 1: The first word is large enough to subtract from directly
  if (*bitarr->words >= value)
  {
    *bitarr->words -= value;
    return 1;
  }

  // Case 2: The first word is too small, we need to borrow from subsequent words
  underflow_amount = value - *bitarr->words;

  // Find the next non-zero word to borrow from
  for (word_idx = 1; word_idx < bitarr->num_of_words; ++word_idx)
  {
    if (bitarr->words[word_idx])
      break;
  }

  // If we reached the end without finding a non-zero word, we underflowed the array
  if (word_idx >= bitarr->num_of_words)
    return 0;

  // Borrow 1 from the found word
  --bitarr->words[word_idx];

  // Set all words between the first and the borrowed word to maximum value (-1)
  for (word_idx = word_idx - 1; word_idx > 0; --word_idx)
  {
    bitarr->words[word_idx] = -1LL;
  }

  // Set the first word to the remaining value after accounting for the borrow.
  // (-1LL - underflow_amount - 1) is mathematically equivalent to ~underflow_amount
  *bitarr->words = ~underflow_amount;

  return 1;
}