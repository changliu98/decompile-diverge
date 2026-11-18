static int bit_array_load(struct bit_array *bitarr, void *data)
{
  unsigned int num_of_bits;
  if (read_all(&num_of_bits, sizeof(num_of_bits), sizeof(num_of_bits), data)
      != sizeof(num_of_bits))
    return 0;
  num_of_bits = ntohl((uint32_t)num_of_bits);
  bitarray_resize(bitarr, num_of_bits);
  unsigned long num_of_bytes = (bitarr->num_of_bits + 7) / 8;
  if (read_all((void *)bitarr->words, sizeof(bitarr->words[0]),
       num_of_bytes, data) != num_of_bytes)
    return 0;
  for (word_addr_t i = 0; i < bitarr->num_of_words; i++)
    bitarr->words[i] = ntohl((uint32_t)bitarr->words[i]);
  mask_top_word(bitarr);
  return 1;
}