void OPL3_ChannelUpdateRhythm(struct OPL3 *opl3, uint8_t data) {
    opl3->rhythm = data & 0x3f;

    if (opl3->rhythm & 0x20) {
        struct OPL3_Channel *chan6 = (struct OPL3_Channel *)((uint8_t *)opl3 + 0x210);
        struct OPL3_Channel *chan7 = (struct OPL3_Channel *)((uint8_t *)opl3 + 0x268);
        struct OPL3_Channel *chan8 = (struct OPL3_Channel *)((uint8_t *)opl3 + 0x2c0);

        // Channel 6 setup
        chan6->modulator = chan6->slots[0] + 1;
        chan6->carrier = chan6->slots[0] + 1;
        chan6->fb_slot1 = &opl3->slots[0];
        chan6->fb_slot2 = &opl3->slots[0];

        // Channel 7 setup
        chan7->modulator = chan7->slots[0] + 1;
        chan7->carrier = chan7->slots[0] + 1;
        chan7->fb_slot1 = chan7->slots[1] + 1;
        chan7->fb_slot2 = chan7->slots[1] + 1;

        // Channel 8 setup
        chan8->modulator = chan8->slots[0] + 1;
        chan8->carrier = chan8->slots[0] + 1;
        chan8->fb_slot1 = chan8->slots[1] + 1;
        chan8->fb_slot2 = chan8->slots[1] + 1;

        for (uint8_t i = 6; i < 9; i++) {
            struct OPL3_Channel *chan = (struct OPL3_Channel *)((uint8_t *)opl3 + i * 0x58);
            chan->rhythm = 3;
        }

        OPL3_ChannelUpdateAlg(chan6);
        OPL3_ChannelUpdateAlg(chan7);
        OPL3_ChannelUpdateAlg(chan8);

        if (opl3->rhythm & 0x1) {
            OPL3_ChannelKeyOn(chan7->slots[0], 2);
        } else {
            OPL3_ChannelKeyOff(chan7->slots[0], 2);
        }

        if (opl3->rhythm & 0x2) {
            OPL3_ChannelKeyOn(chan8->slots[1], 2);
        } else {
            OPL3_ChannelKeyOff(chan8->slots[1], 2);
        }

        if (opl3->rhythm & 0x4) {
            OPL3_ChannelKeyOn(chan8->slots[0], 2);
        } else {
            OPL3_ChannelKeyOff(chan8->slots[0], 2);
        }

        if (opl3->rhythm & 0x8) {
            OPL3_ChannelKeyOn(chan7->slots[1], 2);
        } else {
            OPL3_ChannelKeyOff(chan7->slots[1], 2);
        }

        if (opl3->rhythm & 0x10) {
            OPL3_ChannelKeyOn(chan6->slots[0], 2);
            OPL3_ChannelKeyOn(chan6->slots[1], 2);
        } else {
            OPL3_ChannelKeyOff(chan6->slots[0], 2);
            OPL3_ChannelKeyOff(chan6->slots[1], 2);
        }
    } else {
        for (uint8_t i = 6; i < 9; i++) {
            struct OPL3_Channel *chan = (struct OPL3_Channel *)((uint8_t *)opl3 + i * 0x58);
            chan->rhythm = 0;
            OPL3_ChannelUpdateAlg(chan);
            OPL3_ChannelKeyOff(chan->slots[0], 2);
            OPL3_ChannelKeyOff(chan->slots[1], 2);
        }
    }
}