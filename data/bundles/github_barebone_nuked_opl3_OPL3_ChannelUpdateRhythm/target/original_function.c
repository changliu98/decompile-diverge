static void OPL3_ChannelUpdateRhythm(opl3_chip *chip, uint8_t data)
{
    opl3_channel *channel6;
    opl3_channel *channel7;
    opl3_channel *channel8;
    uint8_t chnum;

    chip->rhy = data & 0x3f;
    if (chip->rhy & 0x20)
    {
        channel6 = &chip->channel[6];
        channel7 = &chip->channel[7];
        channel8 = &chip->channel[8];
        channel6->out[0] = &channel6->slotz[1]->out;
        channel6->out[1] = &channel6->slotz[1]->out;
        channel6->out[2] = &chip->zeromod;
        channel6->out[3] = &chip->zeromod;
        channel7->out[0] = &channel7->slotz[0]->out;
        channel7->out[1] = &channel7->slotz[0]->out;
        channel7->out[2] = &channel7->slotz[1]->out;
        channel7->out[3] = &channel7->slotz[1]->out;
        channel8->out[0] = &channel8->slotz[0]->out;
        channel8->out[1] = &channel8->slotz[0]->out;
        channel8->out[2] = &channel8->slotz[1]->out;
        channel8->out[3] = &channel8->slotz[1]->out;
        for (chnum = 6; chnum < 9; chnum++)
        {
            chip->channel[chnum].chtype = ch_drum;
        }
        OPL3_ChannelSetupAlg(channel6);
        OPL3_ChannelSetupAlg(channel7);
        OPL3_ChannelSetupAlg(channel8);
        /* hh */
        if (chip->rhy & 0x01)
        {
            OPL3_EnvelopeKeyOn(channel7->slotz[0], egk_drum);
        }
        else
        {
            OPL3_EnvelopeKeyOff(channel7->slotz[0], egk_drum);
        }
        /* tc */
        if (chip->rhy & 0x02)
        {
            OPL3_EnvelopeKeyOn(channel8->slotz[1], egk_drum);
        }
        else
        {
            OPL3_EnvelopeKeyOff(channel8->slotz[1], egk_drum);
        }
        /* tom */
        if (chip->rhy & 0x04)
        {
            OPL3_EnvelopeKeyOn(channel8->slotz[0], egk_drum);
        }
        else
        {
            OPL3_EnvelopeKeyOff(channel8->slotz[0], egk_drum);
        }
        /* sd */
        if (chip->rhy & 0x08)
        {
            OPL3_EnvelopeKeyOn(channel7->slotz[1], egk_drum);
        }
        else
        {
            OPL3_EnvelopeKeyOff(channel7->slotz[1], egk_drum);
        }
        /* bd */
        if (chip->rhy & 0x10)
        {
            OPL3_EnvelopeKeyOn(channel6->slotz[0], egk_drum);
            OPL3_EnvelopeKeyOn(channel6->slotz[1], egk_drum);
        }
        else
        {
            OPL3_EnvelopeKeyOff(channel6->slotz[0], egk_drum);
            OPL3_EnvelopeKeyOff(channel6->slotz[1], egk_drum);
        }
    }
    else
    {
        for (chnum = 6; chnum < 9; chnum++)
        {
            chip->channel[chnum].chtype = ch_2op;
            OPL3_ChannelSetupAlg(&chip->channel[chnum]);
            OPL3_EnvelopeKeyOff(chip->channel[chnum].slotz[0], egk_drum);
            OPL3_EnvelopeKeyOff(chip->channel[chnum].slotz[1], egk_drum);
        }
    }
}