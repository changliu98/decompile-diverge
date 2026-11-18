void OPL2_ChannelUpdateRhythm(opl2_chip *chip, uint8_t data)
{
    uint8_t chnum;

    chip->rhy = data & 0x3f;
    if (chip->rhy & 0x20)
    {
        for (chnum = 6; chnum < 9; chnum++)
        {
            chip->channel[chnum].chtype = 1;
        }
        OPL2_ChannelSetupCon(&chip->channel[6]);
        OPL2_ChannelSetupCon(&chip->channel[7]);
        OPL2_ChannelSetupCon(&chip->channel[8]);
        if (chip->rhy & 0x01)
        {
            OPL2_EnvelopeKeyOn(chip->channel[7].slotz[0], 2);
        }
        else
        {
            OPL2_EnvelopeKeyOff(chip->channel[7].slotz[0], 2);
        }
        if (chip->rhy & 0x02)
        {
            OPL2_EnvelopeKeyOn(chip->channel[8].slotz[1], 2);
        }
        else
        {
            OPL2_EnvelopeKeyOff(chip->channel[8].slotz[1], 2);
        }
        if (chip->rhy & 0x04)
        {
            OPL2_EnvelopeKeyOn(chip->channel[8].slotz[0], 2);
        }
        else
        {
            OPL2_EnvelopeKeyOff(chip->channel[8].slotz[0], 2);
        }
        if (chip->rhy & 0x08)
        {
            OPL2_EnvelopeKeyOn(chip->channel[7].slotz[1], 2);
        }
        else
        {
            OPL2_EnvelopeKeyOff(chip->channel[7].slotz[1], 2);
        }
        if (chip->rhy & 0x10)
        {
            OPL2_EnvelopeKeyOn(chip->channel[6].slotz[0], 2);
            OPL2_EnvelopeKeyOn(chip->channel[6].slotz[1], 2);
        }
        else
        {
            OPL2_EnvelopeKeyOff(chip->channel[6].slotz[0], 2);
            OPL2_EnvelopeKeyOff(chip->channel[6].slotz[1], 2);
        }
    }
    else
    {
        for (chnum = 6; chnum < 9; chnum++)
        {
            chip->channel[chnum].chtype = 0;
            OPL2_ChannelSetupCon(&chip->channel[chnum]);
            OPL2_EnvelopeKeyOff(chip->channel[chnum].slotz[0], 2);
            OPL2_EnvelopeKeyOff(chip->channel[chnum].slotz[1], 2);
        }
    }
}