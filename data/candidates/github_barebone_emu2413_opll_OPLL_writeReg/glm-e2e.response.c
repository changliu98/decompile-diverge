void OPLL_writeReg(struct OPLL *opll, int reg, uint8_t data) {
    // Bounds check: register must be < 0x40
    if (reg >= 0x40) {
        return;
    }

    // Remap certain register ranges down by 0x09
    if ((reg >= 0x19 && reg <= 0x1F) ||
        (reg >= 0x29 && reg <= 0x2F) ||
        (reg >= 0x39 && reg <= 0x3F)) {
        reg -= 0x09;
    }

    // Store the raw data into the register array
    ((uint8_t *)opll)[0x28 + reg] = data;

    // Switch on the register index
    switch (reg) {
        case 0x00: // R0: AM, PM, EG, KR, ML
            ((uint32_t *)opll)[0x17A] = (data >> 7) & 1; // 0x5E8
            ((uint32_t *)opll)[0x17B] = (data >> 6) & 1; // 0x5EC
            ((uint32_t *)opll)[0x172] = (data >> 5) & 1; // 0x5C8
            ((uint32_t *)opll)[0x178] = (data >> 4) & 1; // 0x5E0
            ((uint32_t *)opll)[0x173] = data & 0x0F;     // 0x5CC

            for (int i = 0; i < 9; i++) {
                if (((int *)opll)[0x23 + i] == 0) { // 0x8C
                    struct OPLL *slot = (struct OPLL *)(((uint8_t *)opll) + 0xB0 + (i * 2) * 0x48);
                    set_slot_volume(slot, 12);
                }
            }
            break;

        case 0x01: // R1
            ((uint32_t *)opll)[0x187] = (data >> 7) & 1; // 0x61C
            ((uint32_t *)opll)[0x188] = (data >> 6) & 1; // 0x620
            ((uint32_t *)opll)[0x17F] = (data >> 5) & 1; // 0x5FC
            ((uint32_t *)opll)[0x185] = (data >> 4) & 1; // 0x614
            ((uint32_t *)opll)[0x180] = data & 0x0F;     // 0x600

            for (int i = 0; i < 9; i++) {
                if (((int *)opll)[0x23 + i] == 0) {
                    struct OPLL *slot = (struct OPLL *)(((uint8_t *)opll) + 0xB0 + (i * 2 + 1) * 0x48);
                    set_slot_volume(slot, 12);
                }
            }
            break;

        case 0x02: // R2
            ((uint32_t *)opll)[0x179] = (data >> 6) & 3; // 0x5E4
            ((uint32_t *)opll)[0x170] = data & 0x3F;     // 0x5C0

            for (int i = 0; i < 9; i++) {
                if (((int *)opll)[0x23 + i] == 0) {
                    struct OPLL *slot = (struct OPLL *)(((uint8_t *)opll) + 0xB0 + (i * 2) * 0x48);
                    set_slot_volume(slot, 2);
                }
            }
            break;

        case 0x03: // R3
            ((uint32_t *)opll)[0x186] = (data >> 6) & 3; // 0x618
            ((uint32_t *)opll)[0x189] = (data >> 4) & 1; // 0x624
            ((uint32_t *)opll)[0x17C] = (data >> 3) & 1; // 0x5F0
            ((uint32_t *)opll)[0x171] = data & 7;        // 0x5C4

            for (int i = 0; i < 9; i++) {
                if (((int *)opll)[0x23 + i] == 0) {
                    struct OPLL *slot1 = (struct OPLL *)(((uint8_t *)opll) + 0xB0 + (i * 2) * 0x48);
                    set_slot_volume(slot1, 1);
                    struct OPLL *slot2 = (struct OPLL *)(((uint8_t *)opll) + 0xB0 + (i * 2 + 1) * 0x48);
                    set_slot_volume(slot2, 3);
                }
            }
            break;

        case 0x04: // R4
            ((uint32_t *)opll)[0x174] = (data >> 4) & 0x0F; // 0x5D0
            ((uint32_t *)opll)[0x175] = data & 0x0F;        // 0x5D4

            for (int i = 0; i < 9; i++) {
                if (((int *)opll)[0x23 + i] == 0) {
                    struct OPLL *slot = (struct OPLL *)(((uint8_t *)opll) + 0xB0 + (i * 2) * 0x48);
                    set_slot_volume(slot, 8);
                }
            }
            break;

        case 0x05: // R5
            ((uint32_t *)opll)[0x181] = (data >> 4) & 0x0F; // 0x604
            ((uint32_t *)opll)[0x182] = data & 0x0F;        // 0x608

            for (int i = 0; i < 9; i++) {
                if (((int *)opll)[0x23 + i] == 0) {
                    struct OPLL *slot = (struct OPLL *)(((uint8_t *)opll) + 0xB0 + (i * 2 + 1) * 0x48);
                    set_slot_volume(slot, 8);
                }
            }
            break;

        case 0x06: // R6
            ((uint32_t *)opll)[0x176] = (data >> 4) & 0x0F; // 0x5D8
            ((uint32_t *)opll)[0x177] = data & 0x0F;        // 0x5DC

            for (int i = 0; i < 9; i++) {
                if (((int *)opll)[0x23 + i] == 0) {
                    struct OPLL *slot = (struct OPLL *)(((uint8_t *)opll) + 0xB0 + (i * 2) * 0x48);
                    set_slot_volume(slot, 8);
                }
            }
            break;

        case 0x07: // R7
            ((uint32_t *)opll)[0x183] = (data >> 4) & 0x0F; // 0x60C
            ((uint32_t *)opll)[0x184] = data & 0x0F;        // 0x610

            for (int i = 0; i < 9; i++) {
                if (((int *)opll)[0x23 + i] == 0) {
                    struct OPLL *slot = (struct OPLL *)(((uint8_t *)opll) + 0xB0 + (i * 2 + 1) * 0x48);
                    set_slot_volume(slot, 8);
                }
            }
            break;

        case 0x0E: // R0x0E: Rhythm & Instrument control
            if (((uint8_t *)opll)[0x08] == 1) {
                break;
            }
            update_rhythm_mode(opll);
            OPLL_forceRefresh(opll);
            break;

        case 0x10: // R0x10: F-Number Low
            ((uint8_t *)opll)[0x68] = data;
            break;

        case 0x20: // R0x20: F-Number High, Block
            set_fnumber(opll, reg - 0x10, data | ((((uint8_t *)opll)[0x28 + reg + 0x20] & 1) << 8));
            break;

        case 0x30: // R0x30: Sustain, Volume
            set_volume(opll, reg - 0x20, (data & 1) << 8 | ((uint8_t *)opll)[0x28 + reg - 0x10]);
            set_sus_flag(opll, reg - 0x20, (data >> 1) & 7);
            set_block(opll, reg - 0x20, (data >> 5) & 1);
            OPLL_forceRefresh(opll);
            break;

        case 0x36: // R0x36: BD/SD rhythm volume
        case 0x37: // R0x37: TOM/CYM rhythm volume
        case 0x38: // R0x38: HH rhythm volume
            if ((((uint8_t *)opll)[0x36] & 0x20) != 0 && reg >= 0x36) {
                if (reg == 0x37) {
                    struct OPLL *slot = (struct OPLL *)(((uint8_t *)opll) + 0xB0 + 0x3F0);
                    set_slot_volume(slot, ((data >> 4) & 0x0F) << 2);
                } else if (reg == 0x38) {
                    struct OPLL *slot = (struct OPLL *)(((uint8_t *)opll) + 0xB0 + 0x480);
                    set_slot_volume(slot, ((data >> 4) & 0x0F) << 2);
                }
            } else {
                set_volume(opll, reg - 0x30, (data >> 4) & 0x0F);
            }
            set_slot_volume((struct OPLL *)opll, reg - 0x30, (data & 0x0F) << 2);
            break;

        default:
            break;
    }
}