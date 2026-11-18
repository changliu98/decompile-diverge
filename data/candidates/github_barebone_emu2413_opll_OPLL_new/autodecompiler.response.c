OPLL *
OPLL_new (e_uint32 clk, e_uint32 rate)
{
  OPLL *opll;
  e_int32 i;

  if (!table_initialized)
    initializeTables();

  opll = (OPLL *) calloc (1, sizeof (OPLL));
  if (opll == NULL)
    return NULL;

  for( i = 0; i < 19*2; i++ )
    memcpy(&opll->patch[i],&null_patch,sizeof(OPLL_PATCH));

  opll->clk = clk;
  opll->rate = rate;
  opll->mask = 0;
  opll->conv = NULL;
  opll->mix_out[0] = opll->mix_out[1] = 0;
  opll->noise_seed = 0x100;
  opll->rateratio = 0;
  OPLL_reset (opll);
  OPLL_setChipType (opll, 0);
  OPLL_resetPatch (opll, 0);

  return opll;
}