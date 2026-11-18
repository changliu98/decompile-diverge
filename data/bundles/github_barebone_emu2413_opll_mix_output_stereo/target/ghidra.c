void mix_output_stereo(OPLL *opll)

{
  int16_t *piVar1;
  int i;
  int16_t *out;
  OPLL *opll_local;
  
  piVar1 = opll->mix_out;
  opll->mix_out[1] = 0;
  *piVar1 = 0;
  for (i = 0; i < 0xe; i = i + 1) {
    if ((opll->pan[i] & 2) != 0) {
      *piVar1 = *piVar1 + (short)(int)((float)(int)opll->ch_out[i] * opll->pan_fine[i][0]);
    }
    if ((opll->pan[i] & 1) != 0) {
      opll->mix_out[1] =
           opll->mix_out[1] + (short)(int)((float)(int)opll->ch_out[i] * opll->pan_fine[i][1]);
    }
  }
  if (opll->conv != (OPLL_RateConv *)0x0) {
    OPLL_RateConv_putData(opll->conv,0,*piVar1);
    OPLL_RateConv_putData(opll->conv,1,opll->mix_out[1]);
  }
  return;
}