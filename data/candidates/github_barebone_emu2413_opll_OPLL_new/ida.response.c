OPLL *__cdecl OPLL_new(uint32_t clk, uint32_t rate)
{
  int i; // [rsp+4h] [rbp-1Ch]
  OPLL *opll; // [rsp+8h] [rbp-18h]

  if ( !table_initialized )
    initializeTables();
  opll = (OPLL *)calloc(1uLL, 0xE38uLL);
  if ( !opll )
    return 0LL;
  for ( i = 0; i < 38; ++i )
    memcpy(&opll->patch[i], &null_patch, sizeof(opll->patch[i]));
  opll->clk = clk;
  opll->rate = rate;
  opll->mask = 0;
  opll->conv = 0LL;
  opll->mix_out[0] = 0;
  opll->mix_out[1] = 0;
  OPLL_reset(opll);
  OPLL_setChipType(opll, 0);
  OPLL_resetPatch(opll, 0);
  return opll;
}