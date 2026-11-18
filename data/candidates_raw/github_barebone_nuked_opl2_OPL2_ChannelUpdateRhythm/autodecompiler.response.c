void OPL2_WriteRegBuffered(opl2_chip *chip, Bit8u reg, Bit8u v)
{
    Bit64u time1, time2;
    chip->regOpenTable[reg] = v & 0x3f;

    if (chip->regOpenTable[0x07] & 0x20) {
        opl2_channel *chan6 = &chip->channel[6];
        opl2_channel *chan7 = &chip->channel[7];
        opl2_channel *chan8 = &chip->channel[8];
        unsigned char chanNum = 6;

        while (chanNum < 10) {
            chip->channel[chanNum].muted = true;
            chanNum++;
        }

        OPL2_ChannelSetupCon(chan6);
        OPL2_ChannelSetupCon(chan7);
        OPL2_ChannelSetupCon(chan8);

        if (chip->regOpenTable[0x07] & 0x01) {
            OPL2_EnvelopeKeyOn(chan7->slotz[0], 2);
        } else {
            OPL2_EnvelopeKeyOff(chan7->slotz[0], 2);
        }
        if (chip->regOpenTable[0x07] & 0x02) {
            OPL2_EnvelopeKeyOn(chan8->slotz[1], 2);
        } else {
            OPL2_EnvelopeKeyOff(chan8->slotz[1], 2);
        }
        if (chip->regOpenTable[0x07] & 0x04) {
            OPL2_EnvelopeKeyOn(chan8->slotz[0], 2);
        } else {
            OPL2_EnvelopeKeyOff(chan8->slotz[0], 2);
        }
        if (chip->regOpenTable[0x07] & 0x08) {
            OPL2_EnvelopeKeyOn(chan7->slotz[1], 2);
        } else {
            OPL2_EnvelopeKeyOff(chan7->slotz[1], 2);
        }
        if (chip->regOpenTable[0x07] & 0x10) {
            OPL2_EnvelopeKeyOn(chan6->slotz[0], 2);
            OPL2_EnvelopeKeyOn(chan6->slotz[1], 2);
        } else {
            OPL2_EnvelopeKeyOff(chan6->slotz[0], 2);
            OPL2_EnvelopeKeyOff(chan6->slotz[1], 2);
        }
        return;
    }

    chanNum = 6;

    while (chanNum < 10) {
        chip->channel[chanNum].muted = false;
        OPL2_ChannelSetupCon(&chip->channel[chanNum]);
        OPL2_EnvelopeKeyOff(chip->channel[chanNum].slotz[0], 2);
        OPL2_EnvelopeKeyOff(chip->channel[chanNum].slotz[1], 2);
        chanNum++;
    }
}