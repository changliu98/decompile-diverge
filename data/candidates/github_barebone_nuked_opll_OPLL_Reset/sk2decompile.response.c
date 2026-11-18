void OPLL_Reset(OPLL *opll, int type) {
  int i;
  memset(opll, 0, sizeof(OPLL));
  opll->type = type;
  if (type == 1) {
    opll->noise_seed = 0x20;
    opll->noise_shift = 0x80;
  }
  switch (type) {
    case 1:
      opll->chip_info = &OPLL_Type1_Info;
      break;
    case 3:
    case 4:
      opll->chip_info = &OPLL_Type3_Info;
      break;
    case 6:
      opll->chip_info = &OPLL_Type6_Info;
      break;
    default:
      opll->chip_info = &OPLL_Type2_Info;
      break;
  }
  for (i = 0; i < 18; i++) {
    opll->pan[i] = 3;
    opll->volume[i] = 0x7f;
    opll->master_volume = 0x7f;
  }
  opll->eg_timer = 6;
}