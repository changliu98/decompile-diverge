void compute_accelerated_huffman(struct codebook *c)
{
  int i;
  int entries;
  int max_codeword_len = 10;
  for (i = 0; i < (1 << 10); i++)
    c->fast_huffman[i] = -1;
  if (c->sparse)
    entries = c->sorted_entries;
  else
    entries = c->entries;
  for (i = 0; i < ((entries > 32767) ? 32767 : entries); i++) {
    if (c->codeword_lengths[i] > max_codeword_len)
      continue;
    unsigned int codeword;
    if (c->sparse)
      codeword = sparse_codeword_to_codeword(c->sorted_codewords[i]);
    else
      codeword = c->codewords[i];
    unsigned int mask = 1 << c->codeword_lengths[i];
    for (unsigned int j = codeword; j < (1 << 10); j += mask)
      c->fast_huffman[j] = i;
  }
}