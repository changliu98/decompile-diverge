void OPL3_ChannelSet4Op(OPL3_Channel *channels, uint8_t four_op) {
    for (uint8_t i = 0; i < 6; i++) {
        uint8_t j = i;
        if (i >= 3) {
            j += 6;
        }

        if ((four_op >> i) & 1) {
            channels[j].chg = 1;
            channels[j + 3].chg = 2;
            OPL3_ChannelUpdateAlg(&channels[j]);
        } else {
            channels[j].chg = 0;
            channels[j + 3].chg = 0;
            OPL3_ChannelUpdateAlg(&channels[j]);
            OPL3_ChannelUpdateAlg(&channels[j + 3]);
        }
    }
}