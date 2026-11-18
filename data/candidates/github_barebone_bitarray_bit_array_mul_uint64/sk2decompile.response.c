void bit_array_mul_uint64(bit_array_t *ba, unsigned long long int mul) {
  bit_index_t i;
  if (ba->n_bits == 0 || mul == 1) {
    return;
  }
  if (mul == 0) {
    bit_array_clear_all(ba);
    return;
  }
  for (i = ba->n_bits; i > 0; i--) {
    if (((ba->words[(i - 1) >> 6] >> ((i - 1) & 0x3F)) & 1) != 0) {
      ba->words[(i - 1) >> 6] &= ~(1LL << ((i - 1) & 0x3F));
      bit_array_add_word(ba, i - 1, mul);
    }
  }
}