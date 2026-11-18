void OPLL_Reset(opll_t *chip, uint32_t chip_type) {
    uint32_t i;
    memset(chip, 0, sizeof(opll_t));
    chip->chip_type = chip_type;
    if (chip_type == opll_type_ds1001) {
        /* Rhythm mode is always on */
        chip->rhythm = 0x20;
        chip->rm_enable = (int8_t)0x80;
    }
    switch (chip_type) {
    case opll_type_ds1001:
        chip->patchrom = patch_ds1001;
        break;
    case opll_type_ymf281:
    case opll_type_ymf281b:
        chip->patchrom = patch_ymf281;
        break;
    case opll_type_ym2423:
        chip->patchrom = patch_ym2423;
        break;
    case opll_type_ym2413:
    case opll_type_ym2413b:
    case opll_type_ym2420:
    default:
        chip->patchrom = patch_ym2413;
        break;
    }
    for (i = 0; i < 18; i++) {
        chip->eg_state[i] = eg_num_release;
        chip->eg_level[i] = 0x7f;
        chip->eg_out = 0x7f;
    }
    chip->rm_select = rm_num_tc + 1;
}