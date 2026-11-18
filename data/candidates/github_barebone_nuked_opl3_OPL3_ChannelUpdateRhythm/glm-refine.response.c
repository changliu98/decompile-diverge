void __cdecl OPL3_ChannelUpdateRhythm(opl3_chip *chip, uint8_t data)
{
    // Store the lower 6 bits of the data byte (Rhythm mode flags)
    chip->rhy = data & 0x3F;

    // Bit 5 (0x20) enables rhythm mode
    if ((chip->rhy & 0x20) != 0)
    {
        opl3_channel *channel6 = &chip->channel[6];
        opl3_channel *channel7 = &chip->channel[7];
        opl3_channel *channel8 = &chip->channel[8];

        // Route rhythm instrument outputs
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

        // Set channels 6, 7, 8 to rhythm channel type (3)
        for (uint8_t i = 6; i < 9; ++i)
            chip->channel[i].chtype = 3;

        OPL3_ChannelSetupAlg(channel6);
        OPL3_ChannelSetupAlg(channel7);
        OPL3_ChannelSetupAlg(channel8);

        // Bit 0: Bass Drum
        if (chip->rhy & 0x01)
            OPL3_EnvelopeKeyOn(channel7->slotz[0], 2u);
        else
            OPL3_EnvelopeKeyOff(channel7->slotz[0], 2u);

        // Bit 1: Snare Drum
        if (chip->rhy & 0x02)
            OPL3_EnvelopeKeyOn(channel8->slotz[1], 2u);
        else
            OPL3_EnvelopeKeyOff(channel8->slotz[1], 2u);

        // Bit 2: Tom-Tom
        if (chip->rhy & 0x04)
            OPL3_EnvelopeKeyOn(channel8->slotz[0], 2u);
        else
            OPL3_EnvelopeKeyOff(channel8->slotz[0], 2u);

        // Bit 3: Top Cymbal
        if (chip->rhy & 0x08)
            OPL3_EnvelopeKeyOn(channel7->slotz[1], 2u);
        else
            OPL3_EnvelopeKeyOff(channel7->slotz[1], 2u);

        // Bit 4: Hi-Hat
        if (chip->rhy & 0x10)
        {
            OPL3_EnvelopeKeyOn(channel6->slotz[0], 2u);
            OPL3_EnvelopeKeyOn(channel6->slotz[1], 2u);
        }
        else
        {
            OPL3_EnvelopeKeyOff(channel6->slotz[0], 2u);
            OPL3_EnvelopeKeyOff(channel6->slotz[1], 2u);
        }
    }
    else
    {
        // Rhythm mode disabled: revert channels 6, 7, 8 to normal operation
        for (uint8_t i = 6; i < 9; ++i)
        {
            chip->channel[i].chtype = 0;
            OPL3_ChannelSetupAlg(&chip->channel[i]);
            OPL3_EnvelopeKeyOff(chip->channel[i].slotz[0], 2u);
            OPL3_EnvelopeKeyOff(chip->channel[i].slotz[1], 2u);
        }
    }
}