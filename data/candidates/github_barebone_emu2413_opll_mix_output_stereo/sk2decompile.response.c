static void mix_output_stereo(OPLL *opll) {
  int i;
  int16_t *buf = opll->buf;
  buf[1] = 0;
  buf[0] = 0;
  for (i = 0; i < 14; i++) {
    if (opll->pan[i] & 2)
      buf[0] += (int)((float)opll->output[i] * opll->pan_tbl[i][0]);
    if (opll->pan[i] & 1)
      buf[1] += (int)((float)opll->output[i] * opll->pan_tbl[i][1]);
  }
  if (opll->rateconv) {
    OPLL_RateConv_putData(opll->rateconv, 0, buf[0]);
    OPLL_RateConv_putData(opll->rateconv, 1, buf[1]);
  }
}