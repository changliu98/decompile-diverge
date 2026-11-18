char __cdecl bit_array_load(BIT_ARRAY *bitarr, FILE *f)
{
  word_addr_t i;
  size_t num_of_bytes;
  bit_index_t num_bits;

  // Read the number of bits (8 bytes) from the file
  if (fread(&num_bits, 1, 8, f) != 8)
    return 0;

  // Convert from little-endian to host byte order
  num_bits = le64_to_cpu((const uint8_t *)&num_bits);

  // Resize the bit array to accommodate the loaded number of bits
  bit_array_resize_critical(bitarr, num_bits);

  // Calculate the number of bytes needed to store the bits
  num_of_bytes = (bitarr->num_of_bits + 7) >> 3;

  // Read the bit data from the file
  if (fread(bitarr->words, 1, num_of_bytes, f) != num_of_bytes)
    return 0;

  // Convert each word from little-endian to host byte order
  for (i = 0; i < bitarr->num_of_words; ++i)
  {
    bitarr->words[i] = le64_to_cpu((const uint8_t *)&bitarr->words[i]);
  }

  // Mask off any unused bits in the last word
  mask_top_word(bitarr);

  return 1;
}