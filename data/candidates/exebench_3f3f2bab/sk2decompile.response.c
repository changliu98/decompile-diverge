int sboxCHECK(float *sbox, float *sbox_max, int sbox_size) {
  int i;
  if (sbox == NULL || sbox_max == NULL) return 1;
  for (i = 0; i < sbox_size; i++) {
    if (sbox[i] > sbox_max[i]) return 0;
  }
  return 1;
}