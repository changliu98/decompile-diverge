void mix_output_stereo(struct opll *opll)
{
  int i;
  short *out = opll->mix_out;
  out[0] = out[1] = 0;
  for (i = 0; i < 14; i++) {
    if (opll->pan[i] & 0x02)
      out[0] += opll->pan_fine[i][0] * opll->ch_out[i];
    if (opll->pan[i] & 0x01)
      out[1] += opll->pan_fine[i][1] * opll->ch_out[i];
  }
  if (opll->conv != ((void *)0)) {
    opll_conv_put(opll->conv, 0, out[0]);
    opll_conv_put(opll->conv, 1, out[1]);
  }
}