void mix_output_stereo(OPLL *opll)
{
  int i;
  int16_t *mix_out = opll->mix_out;

  mix_out[0] = 0;
  mix_out[1] = 0;

  for (i = 0; i < 14; i++)
  {
    if (opll->pan[i] & 0x02)
    {
      mix_out[0] += (int16_t)(opll->ch_out[i] * opll->pan_fine[i][0]);
    }
    if (opll->pan[i] & 0x01)
    {
      mix_out[1] += (int16_t)(opll->ch_out[i] * opll->pan_fine[i][1]);
    }
  }

  if (opll->conv)
  {
    OPLL_RateConv_putData(opll->conv, 0, mix_out[0]);
    OPLL_RateConv_putData(opll->conv, 1, mix_out[1]);
  }
}