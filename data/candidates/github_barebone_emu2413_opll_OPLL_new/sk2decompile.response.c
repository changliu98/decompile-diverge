OPLL *OPLL_new(int rate, int stereo) {
  OPLL *opll;
  int i;
  if (!initialized) initializeTables();
  opll = (OPLL *)calloc(1, sizeof(OPLL));
  if (opll == NULL) return NULL;
  for (i = 0; i < 38; i++) memcpy(&opll->patch[i], &dummy_patch, 12);
  opll->rate = rate;
  opll->stereo = stereo;
  opll->mask = 0;
  opll->type = 0;
  opll->ssg_out[0] = 0;
  opll->ssg_out[1] = 0;
  OPLL_reset(opll);
  OPLL_setChipType(opll, 0);
  OPLL_resetPatch(opll, 0);
  return opll;
}