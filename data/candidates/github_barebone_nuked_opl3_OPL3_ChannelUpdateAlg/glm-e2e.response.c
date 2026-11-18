void OPL3_ChannelUpdateAlg(void *arg1) {
    unsigned char *channel = (unsigned char *)arg1;
    unsigned char *slot = *(unsigned char **)(channel + 0x10);
    unsigned char *opl3 = *(unsigned char **)(channel + 0x18);

    channel[0x47] = channel[0x46];

    if (opl3[0x1184] != 0) {
        if (channel[0x40] == 1) {
            unsigned char alg = (channel[0x46] << 1) | 0x4 | slot[0x46];
            slot[0x47] = alg;
            channel[0x47] = 0x8;
            OPL3_EnvelopeUpdateKSL(slot);
        } else if (channel[0x40] == 2) {
            unsigned char alg = (slot[0x46] << 1) | 0x4 | channel[0x46];
            channel[0x47] = alg;
            slot[0x47] = 0x8;
            OPL3_EnvelopeUpdateKSL(channel);
        } else {
            OPL3_EnvelopeUpdateKSL(channel);
        }
    } else {
        OPL3_EnvelopeUpdateKSL(channel);
    }
}