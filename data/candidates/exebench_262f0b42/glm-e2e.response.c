void breakup(struct BreakupStruct *output, uint16_t input) {
    // Initialize all 14 elements to 0
    for (int i = 0; i < 14; i++) {
        output->bits[i] = 0;
    }

    // Check and subtract bit values
    if (input >= 0x1000) {
        output->bits[12] = 1;
        input -= 0x1000;
    }
    if (input >= 0x800) {
        output->bits[11] = 1;
        input -= 0x800;
    }
    if (input >= 0x400) {
        output->bits[10] = 1;
        input -= 0x400;
    }
    if (input >= 0x200) {
        output->bits[9] = 1;
        input -= 0x200;
    }
    if (input >= 0x100) {
        output->bits[8] = 1;
        input -= 0x100;
    }
    if (input >= 0x80) {
        output->bits[7] = 1;
        input -= 0x80;
    }
    if (input >= 0x40) {
        output->bits[6] = 1;
        input -= 0x40;
    }
    if (input >= 0x20) {
        output->bits[5] = 1;
        input -= 0x20;
    }
    if (input >= 0x10) {
        output->bits[4] = 1;
        input -= 0x10;
    }
    if (input >= 0x8) {
        output->bits[3] = 1;
        input -= 0x8;
    }
    if (input >= 0x4) {
        output->bits[2] = 1;
        input -= 0x4;
    }
    if (input >= 0x2) {
        output->bits[1] = 1;
        input -= 0x2;
    }
    if (input == 0x1) {
        output->bits[0] = 1;
    }
}