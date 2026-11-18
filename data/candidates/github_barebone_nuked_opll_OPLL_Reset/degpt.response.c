void OPLL_Reset(opll_t *opll, uint32_t type_id)
{
    // Clear the entire chip structure to zero
    memset(opll, 0, 0x188);
    // Store the specific chip type identifier
    opll->chip_type = type_id;
    
    // Configure rhythm-specific settings for chip type 1 (DS-1001)
    if (type_id == 1) {
        opll->rhythm = ' ';
        opll->rm_enable = -0x80;
    }
    
    // Assign the appropriate patch ROM based on chip type
    switch (type_id) {
    case 0:
    case 2:
    case 5:
    default:
        // YM2413 compatible patches
        opll->patchrom = patch_ym2413;
        break;
    case 1:
        // DS-1001 specific patches
        opll->patchrom = patch_ds1001;
        break;
    case 3:
    case 4:
        // YMF281 specific patches
        opll->patchrom = patch_ymf281;
        break;
    case 6:
        // YM2423 specific patches
        opll->patchrom = patch_ym2423;
    }
    
    // Initialize envelope generator state and level for all operators
    for (uint32_t i = 0; i < 0x12; i++) {
        opll->eg_state[i] = '\x03';
        opll->eg_level[i] = '\x7f';
        opll->eg_out = '\x7f';
    }
    // Set rhythm mode select value
    opll->rm_select = 6;
}