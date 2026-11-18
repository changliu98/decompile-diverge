void SCC_reset(struct SCC_State *scc) {
    if (scc == NULL) {
        return;
    }

    scc->field_0x18 = 0;
    scc->field_0x1c = 0;
    scc->field_0x20 = 0x9000;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 32; j++) {
            scc->array_0x48[i][j] = 0;
        }
        scc->array_0xe8[i] = 0;
        scc->array_0xfc[i] = 0;
        scc->array_0x110[i] = 0;
        scc->array_0x124[i] = 0;
        scc->array_0x138[i] = 0;
        scc->array_0x1a0[i] = 0;
        scc->array_0x1b4[i] = 0;
    }

    memset(scc->array_0x14c, 0, 64);

    scc->field_0x24 = 0;
    scc->field_0x18c = 0xff;
    scc->field_0x190 = 0xff;
    scc->field_0x194 = 0;
    scc->field_0x198 = 0;
    scc->field_0x19c = 0;
    scc->field_0x10 = 0;
}