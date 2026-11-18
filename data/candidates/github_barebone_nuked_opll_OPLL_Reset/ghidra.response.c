void OPLL_Reset(opll_t *chip,uint32_t chip_type)

{
  uint32_t i;
  uint32_t chip_type_local;
  opll_t *chip_local;
  
  memset(chip,0,0x188);
  chip->chip_type = chip_type;
  if (chip_type == 1) {
    chip->rhythm = ' ';
    chip->rm_enable = -0x80;
  }
  switch(chip_type) {
  case 0:
  case 2:
  case 5:
  default:
    chip->patchrom = patch_ym2413;
    break;
  case 1:
    chip->patchrom = patch_ds1001;
    break;
  case 3:
  case 4:
    chip->patchrom = patch_ymf281;
    break;
  case 6:
    chip->patchrom = patch_ym2423;
  }
  for (i = 0; i < 0x12; i = i + 1) {
    chip->eg_state[i] = '\x03';
    chip->eg_level[i] = '\x7f';
    chip->eg_out = '\x7f';
  }
  chip->rm_select = 6;
  return;
}