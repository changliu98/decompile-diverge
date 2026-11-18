static void OPL2_ChannelUpdateRhythm(opl2_chip *chip, uint8_t data)
{
    opl2_channel *channel6;
    opl2_channel *channel7;
    opl2_channel *channel8;
    uint8_t chnum;

    chip->rhy = data & 0x3f;
    if (chip->rhy & 0x20)
    {
        channel6 = &chip->channel[6];
        channel7 = &chip->channel[7];
        channel8 = &chip->channel[8];
        for (chnum = 6; chnum < 9; chnum++)
        {
            chip->channel[chnum].chtype = ch_drum;
        }
        OPL2_ChannelSetupCon(channel6);
        OPL2_ChannelSetupCon(channel7);
        OPL2_ChannelSetupCon(channel8);
        /* hh */
        if (chip->rhy & 0x01)
        {
            OPL2_EnvelopeKeyOn(channel7->slotz[0], egk_drum);
        }
        else
        {
            OPL2_EnvelopeKeyOff(channel7->slotz[0], egk_drum);
        }
        /* tc */
        if (chip->rhy & 0x02)
        {
            OPL2_EnvelopeKeyOn(channel8->slotz[1], egk_drum);
        }
        else
        {
            OPL2_EnvelopeKeyOff(channel8->slotz[1], egk_drum);
        }
        /* tom */
        if (chip->rhy & 0x04)
        {
            OPL2_EnvelopeKeyOn(channel8->slotz[0], egk_drum);
        }
        else
        {
            OPL2_EnvelopeKeyOff(channel8->slotz[0], egk_drum);
        }
        /* sd */
        if (chip->rhy & 0x08)
        {
            OPL2_EnvelopeKeyOn(channel7->slotz[1], egk_drum);
        }
        else
        {
            OPL2_EnvelopeKeyOff(channel7->slotz[1], egk_drum);
        }
        /* bd */
        if (chip->rhy & 0x10)
        {
            OPL2_EnvelopeKeyOn(channel6->slotz[0], egk_drum);
            OPL2_EnvelopeKeyOn(channel6->slotz[1], egk_drum);
        }
        else
        {
            OPL2_EnvelopeKeyOff(channel6->slotz[0], egk_drum);
            OPL2_EnvelopeKeyOff(channel6->slotz[1], egk_drum);
        }
    }
    else
    {
        for (chnum = 6; chnum < 9; chnum++)
        {
            chip->channel[chnum].chtype = ch_normal;
            OPL2_ChannelSetupCon(&chip->channel[chnum]);
            OPL2_EnvelopeKeyOff(chip->channel[chnum].slotz[0], egk_drum);
            OPL2_EnvelopeKeyOff(chip->channel[chnum].slotz[1], egk_drum);
        }
    }
}