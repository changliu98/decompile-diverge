static void read_quant_matrix_ext(MpegEncContext *s, GetBitContext *gb) {
  int i;
  if (get_bits1(gb)) {
    for (i = 0; i < 64; i++) {
      int q = get_bits(gb, 8);
      int j = ff_zigzag_direct[i];
      j = s->dsp.idct_permutation[j];
      s->intra_matrix[j] = q;
      j = s->dsp.idct_permutation[j];
      s->inter_matrix[j] = q;
    }
  }
  if (get_bits1(gb)) {
    for (i = 0; i < 64; i++) get_bits(gb, 8);
  }
  if (get_bits1(gb)) {
    for (i = 0; i < 64; i++) {
      int j = s->dsp.idct_permutation[ff_zigzag_direct[i]];
      s->inter_matrix[j] = get_bits(gb, 8);
    }
  }
  if (get_bits1(gb)) {
    for (i = 0; i < 64; i++) get_bits(gb, 8);
  }
  next_start_code_studio(gb);
}