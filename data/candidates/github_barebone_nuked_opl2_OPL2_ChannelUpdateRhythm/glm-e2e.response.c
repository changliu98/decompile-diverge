void OPL2_ChannelUpdateRhythm(struct OPL2_Context *ctx, uint8_t rhythm) {
    // Mask and store the rhythm parameter
    ctx->rhythm_mode = rhythm & 0x3F;

    if ((ctx->rhythm_mode & 0x20) != 0) {
        // Rhythm mode is enabled
        struct OPL2_Context *chan6 = (struct OPL2_Context *)((uint8_t *)ctx + 0xF0);
        struct OPL2_Context *chan7 = (struct OPL2_Context *)((uint8_t *)ctx + 0x118);
        struct OPL2_Context *chan8 = (struct OPL2_Context *)((uint8_t *)ctx + 0x140);

        // Mark channels 6, 7, and 8 as rhythm channels
        for (uint8_t i = 6; i < 9; i++) {
            ((struct OPL2_Context *)((uint8_t *)ctx + i * 0x28))->field_18 = 1;
        }

        // Setup connections for channels 6, 7, and 8
        OPL2_ChannelSetupCon(chan6);
        OPL2_ChannelSetupCon(chan7);
        OPL2_ChannelSetupCon(chan8);

        // Bass Drum (Bit 0)
        if ((ctx->rhythm_mode & 0x01) != 0) {
            OPL2_EnvelopeKeyOn(*(void **)chan7, 2);
        } else {
            OPL2_EnvelopeKeyOff(*(void **)chan7, 2);
        }

        // Snare Drum (Bit 1)
        if ((ctx->rhythm_mode & 0x02) != 0) {
            OPL2_EnvelopeKeyOn(*(void **)((uint8_t *)chan8 + 0x8), 2);
        } else {
            OPL2_EnvelopeKeyOff(*(void **)((uint8_t *)chan8 + 0x8), 2);
        }

        // Tom-Tom (Bit 2)
        if ((ctx->rhythm_mode & 0x04) != 0) {
            OPL2_EnvelopeKeyOn(*(void **)chan8, 2);
        } else {
            OPL2_EnvelopeKeyOff(*(void **)chan8, 2);
        }

        // Top Cymbal (Bit 3)
        if ((ctx->rhythm_mode & 0x08) != 0) {
            OPL2_EnvelopeKeyOn(*(void **)((uint8_t *)chan7 + 0x8), 2);
        } else {
            OPL2_EnvelopeKeyOff(*(void **)((uint8_t *)chan7 + 0x8), 2);
        }

        // Hi-Hat (Bit 4)
        if ((ctx->rhythm_mode & 0x10) != 0) {
            OPL2_EnvelopeKeyOn(*(void **)chan6, 2);
            OPL2_EnvelopeKeyOn(*(void **)((uint8_t *)chan6 + 0x8), 2);
        } else {
            OPL2_EnvelopeKeyOff(*(void **)chan6, 2);
            OPL2_EnvelopeKeyOff(*(void **)((uint8_t *)chan6 + 0x8), 2);
        }
    } else {
        // Rhythm mode is disabled
        for (uint8_t i = 6; i < 9; i++) {
            struct OPL2_Context *chan = (struct OPL2_Context *)((uint8_t *)ctx + i * 0x28);
            chan->field_18 = 0;
            OPL2_ChannelSetupCon(chan);
            OPL2_EnvelopeKeyOff(*(void **)chan, 2);
            OPL2_EnvelopeKeyOff(*(void **)((uint8_t *)chan + 0x8), 2);
        }
    }
}