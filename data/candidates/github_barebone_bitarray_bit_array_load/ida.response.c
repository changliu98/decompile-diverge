char __cdecl bit_array_load(BIT_ARRAY *bitarr, FILE *f)
{
  uint64_t v2; // rax
  word_addr_t i; // [rsp+0h] [rbp-30h]
  size_t num_of_bytes; // [rsp+8h] [rbp-28h]
  bit_index_t num_bits; // [rsp+10h] [rbp-20h] BYREF
  FILE *fa; // [rsp+18h] [rbp-18h]
  BIT_ARRAY *bitarra; // [rsp+20h] [rbp-10h]

  bitarra = bitarr;
  fa = f;
  if ( fread(&num_bits, 1uLL, 8uLL, f) != 8 )
    return 0;
  num_bits = le64_to_cpu((const uint8_t *)&num_bits);
  bit_array_resize_critical(bitarra, num_bits);
  num_of_bytes = (bitarra->num_of_bits + 7) >> 3;
  if ( fread(bitarra->words, 1uLL, num_of_bytes, fa) != num_of_bytes )
    return 0;
  for ( i = 0LL; i < bitarra->num_of_words; ++i )
  {
    v2 = le64_to_cpu((const uint8_t *)&bitarra->words[i]);
    bitarra->words[i] = v2;
  }
  mask_top_word(bitarra);
  return 1;
}