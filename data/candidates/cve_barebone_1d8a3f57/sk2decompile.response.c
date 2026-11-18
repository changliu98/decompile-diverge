int stszin(int size) {
  unsigned int sum, sz;
  unsigned int i;
  u32in();
  u32in();
  stsz_entries = u32in();
  stsz_offsets = malloc(sizeof(unsigned int) * (stsz_entries + 1));
  if (stsz_offsets == NULL) return -1;
  sum = 0;
  stsz_offsets[0] = 0;
  for (i = 0; i < stsz_entries; i++) {
    sz = u32in();
    sum += sz;
    if (sz > stsz_max_entry_size) stsz_max_entry_size = sz;
    stsz_offsets[i + 1] = sum;
    if (sum < stsz_offsets[i]) return -1;
  }
  return size;
}