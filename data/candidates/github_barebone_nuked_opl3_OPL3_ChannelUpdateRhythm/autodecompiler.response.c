void OPL3_ChannelUpdateRhythm(opl3_chip *chip, Bit8u reg, Bit8u v)
{
    opl3_channel *chan;
    opl3_channel *chan1;
    opl3_channel *chan2;
    unsigned char slotnum;

    chip->reg20 = reg & 0x3f;

    if (chip->reg20 & 0x20)
    {
        chan1 = &chip->channel[6];
        chan2 = &chip->channel[7];
        chan = &chip->channel[8];
        chan1->slots[0].trem = &chip->tremolo[2];
        chan1->slots[1].trem = &chip->tremolo[2];
        chan2->slots[0].trem = &chip->tremolo[2];
        chan2->slots[1].trem = &chip->tremolo[2];
        chan->slots[0].trem = &chip->tremolo[2];
        chan->slots[1].trem = &chip->tremolo[2];

        for (slotnum = 6; slotnum < 9; slotnum++)
        {
            chip->channel[slotnum].chtype = 3;
        }

        OPL3_ChannelSetupAlg(chan1);
        OPL3_ChannelSetupAlg(chan2);
        OPL3_ChannelSetupAlg(chan);

        if (chip->reg20 & 0x01)
        {
            OPL3_EnvelopeKeyOn(chan2->slots[0], 2);
        }
        else
        {
            OPL3_EnvelopeKeyOff(chan2->slots[0], 2);
        }

        if (chip->reg20 & 0x02)
        {
            OPL3_EnvelopeKeyOn(chan->slots[1], 2);
        }
        else
        {
            OPL3_EnvelopeKeyOff(chan->slots[1], 2);
        }

        if (chip->reg20 & 0x04)
        {
            OPL3_EnvelopeKeyOn(chan->slots[0], 2);
        }
        else
        {
            OPL3_EnvelopeKeyOff(chan->slots[0], 2);
        }

        if (chip->reg20 & 0x08)
        {
            OPL3_EnvelopeKeyOn(chan2->slots[1], 2);
        }
        else
        {
            OPL3_EnvelopeKeyOff(chan2->slots[1], 2);
        }

        if (chip->reg20 & 0x10)
        {
            OPL3_EnvelopeKeyOn(chan1->slots[0], 2);
            OPL3_EnvelopeKeyOn(chan1->slots[1], 2);
        }
        else
        {
            OPL3_EnvelopeKeyOff(chan1->slots[0], 2);
            OPL3_EnvelopeKeyOff(chan1->slots[1], 2);
        }
    }
    else
    {
        for (slotnum = 6; slotnum < 10; slotnum++)
        {
            chip->channel[slotnum].chtype = 0;
            OPL3_ChannelSetupAlg(&chip->channel[slotnum]);
            OPL3_EnvelopeKeyOff(&chip->channel[slotnum].slots[0], 2);
            OPL3_EnvelopeKeyOff(&chip->channel[slotnum].slots[1], 2);
        }
    }
}