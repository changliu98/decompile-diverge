char bit_array_load(BIT_ARRAY* bitarr, FILE* f)
{
  word_addr_t i;
  word_addr_t num_of_words;
  unsigned long long num_of_bits;

  if(fread(&num_of_bits, sizeof(unsigned long long), 1, f) != 1)
  {
    { do { char _m; _m = (0); } while(0); };
    return 0;
  }

  num_of_bits = le64_to_cpu(num_of_bits);

  bit_array_resize_critical(bitarr, num_of_bits);

  num_of_words = (((bitarr)->num_of_bits + (sizeof(word_t)*8) - 1)/(sizeof(word_t)*8));

  if(fread(bitarr->words, 1, num_of_words*sizeof(word_t), f) != num_of_words*sizeof(word_t))
  {
    { do { char _m; _m = (0); } while(0); };
    return 0;
  }

  for(i = 0; i < bitarr->num_of_words; i++)
  {
    bitarr->words[i] = le64_to_cpu(bitarr->words[i]);
  }

  _mask_top_word(bitarr);

  return 1;
}