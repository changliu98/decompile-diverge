void OPL2_ChannelUpdateRhythm(opl2_chip *opl2, uint8_t rhythm_register)
{
    // Store the rhythm control bits (lower 6 bits of the register)
    opl2->rhy = rhythm_register & 0x3f;
    
    // Check if rhythm mode is disabled (bit 5 is 0)
    if ((opl2->rhy & 0x20) == 0) {
        // Disable rhythm mode: reset channels 6-8 to normal operator mode
        for (uint8_t channel_index = 6; channel_index < 9; channel_index++) {
            // Set channel type to normal (non-rhythm)
            opl2->channel[channel_index].chtype = 0;
            // Reconfigure channel connections for normal operation
            OPL2_ChannelSetupCon(opl2->channel + channel_index);
            // Turn off envelopes for both slots in each channel
            OPL2_EnvelopeKeyOff(opl2->channel[channel_index].slotz[0], 2);
            OPL2_EnvelopeKeyOff(opl2->channel[channel_index].slotz[1], 2);
        }
    } else {
        // Enable rhythm mode: set channels 6-8 to rhythm operator mode
        for (uint8_t channel_index = 6; channel_index < 9; channel_index++) {
            // Set channel type to rhythm
            opl2->channel[channel_index].chtype = 1;
        }
        // Reconfigure channel connections for rhythm operation
        OPL2_ChannelSetupCon(opl2->channel + 6);
        OPL2_ChannelSetupCon(opl2->channel + 7);
        OPL2_ChannelSetupCon(opl2->channel + 8);
        
        // Turn off all envelopes for rhythm channels to reset state
        OPL2_EnvelopeKeyOff(opl2->channel[7].slotz[0], 2);
        OPL2_EnvelopeKeyOff(opl2->channel[8].slotz[1], 2);
        OPL2_EnvelopeKeyOff(opl2->channel[8].slotz[0], 2);
        OPL2_EnvelopeKeyOff(opl2->channel[7].slotz[1], 2);
        OPL2_EnvelopeKeyOff(opl2->channel[6].slotz[0], 2);
        OPL2_EnvelopeKeyOff(opl2->channel[6].slotz[1], 2);

        // Enable specific envelopes based on rhythm bit settings
        // Bit 0: Bass Drum (channel 7, slot 0)
        if (opl2->rhy & 1) OPL2_EnvelopeKeyOn(opl2->channel[7].slotz[0], 2);
        // Bit 1: Snare Drum (channel 8, slot 1)
        if (opl2->rhy & 2) OPL2_EnvelopeKeyOn(opl2->channel[8].slotz[1], 2);
        // Bit 2: Tom-Tom (channel 8, slot 0)
        if (opl2->rhy & 4) OPL2_EnvelopeKeyOn(opl2->channel[8].slotz[0], 2);
        // Bit 3: Top Cymbal (channel 7, slot 1)
        if (opl2->rhy & 8) OPL2_EnvelopeKeyOn(opl2->channel[7].slotz[1], 2);
        // Bit 4: Hi-Hat (channels 6, slots 0 and 1)
        if (opl2->rhy & 0x10) {
            OPL2_EnvelopeKeyOn(opl2->channel[6].slotz[0], 2);
            OPL2_EnvelopeKeyOn(opl2->channel[6].slotz[1], 2);
        }
    }
}