void __cdecl mix_output_stereo(OPLL *opll)
{
  int i; // [rsp+Ch] [rbp-14h]
  int16_t *out; // [rsp+10h] [rbp-10h]

  out = opll->mix_out;
  opll->mix_out[1] = 0;
  opll->mix_out[0] = 0;
  for ( i = 0; i < 14; ++i )
  {
    if ( (opll->pan[i] & 2) != 0 )
      *out += (int)(float)((float)opll->ch_out[i] * opll->pan_fine[i][0]);
    if ( (opll->pan[i] & 1) != 0 )
      opll->mix_out[1] += (int)(float)((float)opll->ch_out[i] * opll->pan_fine[i][1]);
  }
  if ( opll->conv )
  {
    OPLL_RateConv_putData(opll->conv, 0, *out);
    OPLL_RateConv_putData(opll->conv, 1, opll->mix_out[1]);
  }
}