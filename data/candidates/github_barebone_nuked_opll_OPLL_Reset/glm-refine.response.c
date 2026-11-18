define CHIP_TYPE_YM2423   6

void __cdecl OPLL_Reset(opll_t *chip, uint32_t chip_type)
{
  uint32_t i;

  // Initialize the chip state to zero
  memset(chip, 0, sizeof(opll_t));
  chip->chip_type = chip_type;

  // VRC7 (chip_type == 1) lacks hardware rhythm mode and uses a fixed patch set
  if (chip_type == CHIP_TYPE_VRC7) 
  {
    chip->rhythm = 32;
    chip->rm_enable = 0x80;
  }

  // Assign the correct hardware patch ROM based on the chip type
  switch (chip_type)
  {
    case CHIP_TYPE_VRC7:
      chip->patchrom = (const opll_patch_t *)&patch_ds1001;
      break;
    case CHIP_TYPE_YMF281:
    case CHIP_TYPE_YMF281B:
      chip->patchrom = (const opll_patch_t *)&patch_ymf281;
      break;
    case CHIP_TYPE_YM2423:
      chip->patchrom = (const opll_patch_t *)&patch_ym2423;
      break;
    default:
      // Default to standard YM2413 patch ROM
      chip->patchrom = (const opll_patch_t *)&patch_ym2413;
      break;
  }

  // Initialize Envelope Generator (EG) state for all 18 channels/operators (0x12 = 18)
  for (i = 0; i < 0x12; ++i)
  {
    chip->eg_state[i] = 3;    // 3 typically represents the 'Release' phase in OPLL EG state machines
    chip->eg_level[i] = 127;  // Maximum attenuation (silent)
  }
  
  // Note: eg_out is written outside the loop in the original code, effectively 
  // only retaining the value from the last iteration (i = 17).
  chip->eg_out = 127;         

  // Initialize rhythm mode selection
  chip->rm_select = 6;
}