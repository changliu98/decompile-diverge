Assumed global template

struct OPLL *OPLL_new(uint32_t clock, uint32_t rate) {
    struct OPLL *opll;

    // 0xe: Check a global flag (likely to ensure tables are initialized once)
    // If not initialized, call OPLL_initializeTables()
    if (!tables_initialized) {
        OPLL_initializeTables();
    }

    // 0x20 - 0x2a: Allocate memory. 0xe38 is exactly sizeof(struct OPLL)
    opll = calloc(1, 0xe38);

    // 0x33 - 0x46: If allocation fails, return NULL
    if (opll == NULL) {
        return NULL;
    }

    // 0x4b - 0x8c: Loop 38 times (0 to 37)
    // Copies a 0x34-byte template into each slot array entry
    for (int i = 0; i < 38; i++) {
        memcpy(&opll->slots[i], &default_slot_template, 0x34);
    }

    // 0x91 - 0xa1: Store clock and rate into the struct
    opll->clock = clock;
    opll->rate = rate;

    // 0xa4 - 0xd2: Initialize various fields to 0
    // (Though calloc already zeroed them, the compiler explicitly emitted stores)
    opll->quality = 0;
    opll->ptr = NULL;
    opll->mask = 0;
    opll->mask2 = 0;

    // 0xdb - 0xf5: Call initialization routines
    OPLL_reset(opll);
    OPLL_setRate(opll, 0);
    OPLL_setQuality(opll, 0);

    // 0xfa - 0x10b: Return the pointer
    return opll;
}