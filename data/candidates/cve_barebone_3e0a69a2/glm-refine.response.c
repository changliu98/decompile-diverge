void __cdecl read_quant_matrix_ext(MpegEncContext *s, GetBitContext *gb)
{
  uint16_t v;
  int i, j;

  // Load intra matrix
  if (get_bits1(gb))
  {
    for (i = 0; i < 64; ++i)
    {
      v = get_bits(gb, 8);
      j = s->idsp.idct_permutation[ff_zigzag_direct[i]];
      s->intra_matrix[j] = v;
      s->chroma_intra_matrix[j] = v;
    }
  }

  // Load non-intra matrix
  if (get_bits1(gb))
  {
    for (i = 0; i < 64; ++i)
      get_bits(gb, 8);
  }

  // Load chroma intra matrix
  if (get_bits1(gb))
  {
    for (i = 0; i < 64; ++i)
      s->chroma_intra_matrix[s->idsp.idct_permutation[ff_zigzag_direct[i]]] = get_bits(gb, 8);
  }

  // Load chroma non-intra matrix
  if (get_bits1(gb))
  {
    for (i = 0; i < 64; ++i)
      get_bits(gb, 8);
  }

  next_start_code_studio(gb);
}