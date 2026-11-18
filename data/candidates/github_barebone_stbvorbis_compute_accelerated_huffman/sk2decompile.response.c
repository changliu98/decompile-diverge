static void compute_accelerated_huffman(HYuvContext *s) {
  int i, n, j;
  unsigned int code;
  for (i = 0; i < 1024; i++) s->accel_huff_table[i] = -1;
  n = s->is_420 ? s->nb_420_ac_coeffs : s->nb_422_ac_coeffs;
  if (n >= 32768) n = 32768 - 1;
  for (j = 0; j < n; j++) {
    if (s->ac_run_code_lengths[j] <= 10) {
      code = s->is_420 ? bit_reverse(s->ac_run_code_lengths_420[j])
                       : s->ac_run_code_lengths_422[j];
      while (code < 1024) {
        s->accel_huff_table[code] = j;
        code += 1 << s->ac_run_code_lengths[j];
      }
    }
  }
}