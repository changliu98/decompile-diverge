void OPL3_ChannelUpdateRhythm(opl3_chip *chip, uint8_t data)
{
    uint8_t i;

    chip->rhy = data & 0x3f;
    if (chip->rhy & 0x20)
    {
        for (i = 6; i < 9; i++)
        {
            chip->channel[i].out[0] = &chip->channel[i].slotz[1]->out;
            chip->channel[i].out[1] = &chip->channel[i].slotz[1]->out;
            chip->channel[i].out[2] = &chip->zeromod;
            chip->channel[i].out[3] = &chip->zeromod;
        }
        chip->channel[6].out[0] = &chip->channel[6].slotz[0]->out;
        chip->channel[6].out[1] = &chip->channel[6].slotz[0]->out;
        chip->channel[7].out[0] = &chip->channel[7].slotz[0]->out;
        chip->channel[7].out[1] = &chip->channel[7].slotz[0]->out;
        chip->channel[8].out[0] = &chip->channel[8].slotz[0]->out;
        chip->channel[8].out[1] = &chip->channel[8].slotz[0]->out;
        for (i = 6; i < 9; i++)
        {
            chip->channel[i].chtype = 3;
        }
        OPL3_ChannelSetupAlg(&chip->channel[6]);
        OPL3_ChannelSetupAlg(&chip->channel[7]);
        OPL3_ChannelSetupAlg(&chip->channel[8]);
        if (chip->rhy & 0x01)
        {
            OPL3_EnvelopeKeyOn(chip->channel[7].slotz[0], 2);
        }
        else
        {
            OPL3_EnvelopeKeyOff(chip->channel[7].slotz[0], 2);
        }
        if (chip->rhy & 0x02)
        {
            OPL3_EnvelopeKeyOn(chip->channel[8].slotz[1], 2);
        }
        else
        {
            OPL3_EnvelopeKeyOff(chip->channel[8].slotz[1], 2);
        }
        if (chip->rhy & 0x04)
        {
            OPL3_EnvelopeKeyOn(chip->channel[8].slotz[0], 2);
        }
        else
        {
            OPL3_EnvelopeKeyOff(chip->channel[8].slotz[0], 2);
        }
        if (chip->rhy & 0x08)
        {
            OPL3_EnvelopeKeyOn(chip->channel[7].slotz[1], 2);
        }
        else
        {
            OPL3_EnvelopeKeyOff(chip->channel[7].slotz[1], 2);
        }
        if (chip->rhy & 0x10)
        {
            OPL3_EnvelopeKeyOn(chip->channel[6].slotz[0], 2);
            OPL3_EnvelopeKeyOn(chip->channel[6].slotz[1], 2);
        }
        else
        {
            OPL3_EnvelopeKeyOff(chip->channel[6].slotz[0], 2);
            OPL3_EnvelopeKeyOff(chip->channel[6].slotz[1], 2);
        }
    }
    else
    {
        for (i = 6; i < 9; i++)
        {
            chip->channel[i].chtype = 0;
            OPL3_ChannelSetupAlg(&chip->channel[i]);
            OPL3_EnvelopeKeyOff(chip->channel[i].slotz[0], 2);
            OPL3_EnvelopeKeyOff(chip->channel[i].slotz[1], 2);
        }
    }
}