char bit_array_load(BIT_ARRAY* bitarr, FILE* f)
{
  // Read in number of bits, return 0 if we can't read in
  bit_index_t num_bits;
  if(fread(&num_bits, 1, 8, f) != 8) return 0;
  num_bits = le64_to_cpu((uint8_t*)&num_bits);

  // Resize
  bit_array_resize_critical(bitarr, num_bits);

  // Have to calculate how many bytes are needed for the file
  // (Note: this may be different from num_of_words * sizeof(word_t))
  bit_index_t num_of_bytes = roundup_bits2bytes(bitarr->num_of_bits);
  if(fread(bitarr->words, 1, num_of_bytes, f) != num_of_bytes) return 0;

  // Fix endianness
  word_addr_t i;
  for(i = 0; i < bitarr->num_of_words; i++)
    bitarr->words[i] = le64_to_cpu((uint8_t*)&bitarr->words[i]);

  // Mask top word
  _mask_top_word(bitarr);
  DEBUG_VALIDATE(bitarr);
  return 1;
}