void compute_accelerated_huffman(Codebook *c)

{
  uint local_24;
  int local_20;
  uint32 z;
  int len;
  int i;
  Codebook *c_local;
  
  for (i = 0; i < 0x400; i = i + 1) {
    c->fast_huffman[i] = -1;
  }
  if (c->sparse == '\0') {
    local_20 = c->entries;
  }
  else {
    local_20 = c->sorted_entries;
  }
  len = local_20;
  if (0x7fff < local_20) {
    len = 0x7fff;
  }
  for (i = 0; i < len; i = i + 1) {
    if (c->codeword_lengths[i] < 0xb) {
      if (c->sparse == '\0') {
        local_24 = c->codewords[i];
      }
      else {
        local_24 = bit_reverse(c->sorted_codewords[i]);
      }
      for (z = local_24; z < 0x400; z = (1 << (c->codeword_lengths[i] & 0x1f)) + z) {
        c->fast_huffman[z] = (int16)i;
      }
    }
  }
  return;
}