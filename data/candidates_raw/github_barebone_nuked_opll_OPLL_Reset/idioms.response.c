void opll_init(struct opll_t *chip, enum opll_chip_t chip_type)
{
  unsigned int i;
  memset(chip, 0, sizeof(*chip));
  chip->chip_type = chip_type;
  if (chip_type == OPLL_DS1001) {
    chip->rhythm = 32;
    chip->rm_enable = 0x80;
  }
  switch (chip_type) {
    case OPLL_DS1001:
      chip->patchrom = patch_ds1001;
      break;
    case OPLL_YMF281:
    case OPLL_YMF282:
      chip->patchrom = patch_ymf281;
      break;
    case OPLL_YM2423:
      chip->patchrom = patch_ym2423;
      break;
    default:
      chip->patchrom = patch_ym2413;
      break;
  }
  for (i = 0; i < 18; i++) {
    chip->eg_state[i] = OPLL_EG_OFF;
    chip->eg_level[i] = 127;
    chip->eg_out = 127;
  }
  chip->rm_select = 6;
}