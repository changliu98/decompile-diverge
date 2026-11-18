void __cdecl OPLL_Reset(opll_t *chip, uint32_t chip_type)
{
  uint32_t i; // [rsp+10h] [rbp-10h]

  memset(chip, 0, sizeof(opll_t));
  chip->chip_type = chip_type;
  if ( chip_type == 1 )
  {
    chip->rhythm = 32;
    chip->rm_enable = 0x80;
  }
  switch ( chip_type )
  {
    case 1u:
      chip->patchrom = (const opll_patch_t *)&patch_ds1001;
      break;
    case 3u:
    case 4u:
      chip->patchrom = (const opll_patch_t *)&patch_ymf281;
      break;
    case 6u:
      chip->patchrom = (const opll_patch_t *)&patch_ym2423;
      break;
    default:
      chip->patchrom = (const opll_patch_t *)&patch_ym2413;
      break;
  }
  for ( i = 0; i < 0x12; ++i )
  {
    chip->eg_state[i] = 3;
    chip->eg_level[i] = 127;
    chip->eg_out = 127;
  }
  chip->rm_select = 6;
}