INLINE static void mix_output_stereo(OPLL *opll) {
  int16_t *out = opll->mix_out;
  int i;
  out[0] = out[1] = 0;
  for (i = 0; i < 14; i++) {
    if (opll->pan[i] & 2)
      out[0] += (int16_t)(opll->ch_out[i] * opll->pan_fine[i][0]);
    if (opll->pan[i] & 1)
      out[1] += (int16_t)(opll->ch_out[i] * opll->pan_fine[i][1]);
  }
  if (opll->conv) {
    OPLL_RateConv_putData(opll->conv, 0, out[0]);
    OPLL_RateConv_putData(opll->conv, 1, out[1]);
  }
}