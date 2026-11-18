void compute_accelerated_huffman(Codebook *c)
{
   uint32 i, len, entry, z;

   for (i=0; i < (1 << 10); ++i)
      c->fast_huffman[i] = -1;

   if (c->sparse) {
      len = c->sorted_entries;
      if (len > 32767) len = 32767;
      for (entry=0; entry < len; ++entry) {
         if (c->codeword_lengths[entry] <= 10) {
            uint32 z = bit_reverse(c->sorted_codewords[entry]) >> (10 - c->codeword_lengths[entry]);
            for (i=z; i < (1 << 10); i += 1 << c->codeword_lengths[entry])
               c->fast_huffman[i] = (int16) entry;
         }
      }
   } else {
      len = c->entries;
      if (len > 32767) len = 32767;
      for (entry=0; entry < len; ++entry) {
         if (c->codeword_lengths[entry] <= 10) {
            uint32 z = c->codewords[entry] >> (10 - c->codeword_lengths[entry]);
            for (i=z; i < (1 << 10); i += 1 << c->codeword_lengths[entry])
               c->fast_huffman[i] = (int16) entry;
         }
      }
   }
}