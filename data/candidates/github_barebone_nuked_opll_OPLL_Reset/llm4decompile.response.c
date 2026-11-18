void OPLL_Reset(opll_t *chip, uint32_t chip_type)
{
    uint32_t i;

    memset(chip, 0, sizeof(opll_t));
    chip->chip_type = chip_type;

    if (chip_type == 1)
    {
        chip->rhythm = 0x20;
        chip->rm_enable = ~0x7f;
    }

    switch (chip_type)
    {
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
        break;
    }

    for (i = 0; i < 18; i++)
    {
        chip->eg_state[i] = 3;
        chip->eg_level[i] = 0x7f;
        chip->eg_out = 0x7f;
    }

    chip->rm_select = 0x06;
}