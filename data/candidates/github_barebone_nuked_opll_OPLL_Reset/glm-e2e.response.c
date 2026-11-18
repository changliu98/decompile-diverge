void OPLL_Reset(struct OPLL *opll, int type) {
    memset(opll, 0, 0x188);
    opll->type = type;

    if (type == 1) {
        opll->reg_0x14 = 0x20;
        opll->reg_0x15 = 0x80;
    }

    switch (type) {
        case 0:
            opll->patch = patch_ds1001;
            break;
        case 1:
            opll->patch = patch_ymf281;
            break;
        case 2:
            opll->patch = patch_ym2423;
            break;
        case 3:
        case 4:
        case 5:
        case 6:
            // Fallthrough to default (handled by jump table bounds check)
        default:
            opll->patch = patch_ym2413;
            break;
    }

    for (int i = 0; i < 18; i++) {
        opll->ch_status[i] = 0x03;
        opll->rhythm_volume = 0x7f;
    }

    opll->clock = 6;
}