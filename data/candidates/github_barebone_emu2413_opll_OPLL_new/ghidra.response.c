OPLL * OPLL_new(uint32_t clk,uint32_t rate)

{
  int i;
  OPLL *opll;
  uint32_t rate_local;
  uint32_t clk_local;
  OPLL *local_10;
  
  if (table_initialized == '\0') {
    initializeTables();
  }
  local_10 = calloc(1,0xe38);
  if (local_10 == (OPLL *)0x0) {
    local_10 = (OPLL *)0x0;
  }
  else {
    for (i = 0; i < 0x26; i = i + 1) {
      memcpy(local_10->patch + i,&null_patch,0x34);
    }
    local_10->clk = clk;
    local_10->rate = rate;
    local_10->mask = 0;
    local_10->conv = (OPLL_RateConv *)0x0;
    local_10->mix_out[0] = 0;
    local_10->mix_out[1] = 0;
    OPLL_reset(local_10);
    OPLL_setChipType(local_10,'\0');
    OPLL_resetPatch(local_10,'\0');
  }
  return local_10;
}