unsigned gf32_mod (unsigned long long r, int high_bit) {
  int j = high_bit;
  for (j = high_bit; j >= 32; j--) {
    if ((1ULL << j) & r) {
      r ^= 0x1EDC6F41ULL << (j - 32);
    }
  }
  return (unsigned) r;
}