struct OPLL *OPLL_new(unsigned int clk, unsigned int rate)
{
  int i;
  if (!table_initialized)
    initializeTables();
  struct OPLL *opll = (OPLL*)calloc(1, sizeof(OPLL));
  if (!opll)
    return ((void *)0);
  for (i = 0; i < 38; i++)
    memcpy(&opll->patch[i], &null_patch, sizeof(OPLLPatch));
  opll->clk = clk;
  opll->rate = rate;
  opll->mask = 0;
  opll->conv = ((void *)0);
  opll->mix_out[0] = 0;
  opll->mix_out[1] = 0;
  OPLL_reset(opll);
  OPLL_setChipType(opll, 0);
  OPLL_resetPatch(opll, 0);
  return opll;
}