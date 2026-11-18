define MAX_ACCEL_ENTRIES 0x7FFF

void __cdecl compute_accelerated_huffman(Codebook *c)
{
  uint32_t base_codeword; 
  int entry_count;
  int max_entries;
  uint32_t z;
  int i;

  // Initialize the fast lookup table with invalid entries (-1)
  for (i = 0; i < FAST_HUFFMAN_TABLE_SIZE; ++i)
    c->fast_huffman[i] = -1;

  // Determine the number of entries to process based on sparseness
  entry_count = c->sparse ? c->sorted_entries : c->entries;

  // Cap the number of entries to prevent overflow or excessive processing
  max_entries = (entry_count > MAX_ACCEL_ENTRIES) ? MAX_ACCEL_ENTRIES : entry_count;

  // Populate the fast lookup table for short codewords
  for (i = 0; i < max_entries; ++i)
  {
    if (c->codeword_lengths[i] <= FAST_HUFFMAN_MAX_LENGTH)
    {
      // Get the starting codeword. If sparse, use the bit-reversed sorted codeword.
      // Otherwise, use the codeword directly.
      if (c->sparse)
        base_codeword = bit_reverse(c->sorted_codewords[i]);
      else
        base_codeword = c->codewords[i];

      // Fill all possible suffixes for this codeword length in the lookup table.
      // The step size (1 << length) ensures we hit all bit patterns that start with this codeword.
      uint32_t step = 1 << c->codeword_lengths[i];
      for (z = base_codeword; z < FAST_HUFFMAN_TABLE_SIZE; z += step)
        c->fast_huffman[z] = i;
    }
  }
}