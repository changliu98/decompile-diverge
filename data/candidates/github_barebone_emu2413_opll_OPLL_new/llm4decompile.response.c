OPLL *OPLL_new(unsigned int clk, unsigned int rate)
{
    OPLL *chip;
    int i;

    if (!table_initialized)
        initializeTables();

    chip = calloc(1, sizeof(OPLL) + sizeof(OPLL_RateConv));
    if (!chip)
        return NULL;

    for (i = 0; i < 38; i++)
        memcpy(&chip->patch[i], &null_patch, sizeof(OPLL_PATCH));

    chip->clk = clk;
    chip->rate = rate;
    chip->mask = 0;
    chip->conv = (OPLL_RateConv *) (chip + 1);
    chip->mix_out[0] = 0;
    chip->mix_out[1] = 0;

    OPLL_reset(chip);
    OPLL_setChipType(chip, 0);
    OPLL_resetPatch(chip, 0);

    return chip;
}