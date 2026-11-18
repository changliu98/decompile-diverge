void __cdecl OPL2_ChannelUpdateRhythm(opl2_chip *chip, uint8_t data)
{
  // The lower 6 bits of the data byte control the rhythm mode and instruments
  chip->rhy = data & 0x3F;

  // Bit 5 (0x20) enables the OPL2 rhythm mode
  if (chip->rhy & 0x20)
  {
    // Cache pointers to rhythm channels 6, 7, and 8
    opl2_channel *channel6 = &chip->channel[6];
    opl2_channel *channel7 = &chip->channel[7];
    opl2_channel *channel8 = &chip->channel[8];

    // Set channel type to rhythm mode (1)
    for (uint8_t i = 6; i < 9; ++i)
      chip->channel[i].chtype = 1;

    OPL2_ChannelSetupCon(channel6);
    OPL2_ChannelSetupCon(channel7);
    OPL2_ChannelSetupCon(channel8);

    // Bit 0: Bass Drum (Channel 7, Slot 1)
    if (chip->rhy & 0x01)
      OPL2_EnvelopeKeyOn(channel7->slotz[0], 2u);
    else
      OPL2_EnvelopeKeyOff(channel7->slotz[0], 2u);

    // Bit 1: Snare Drum (Channel 8, Slot 2)
    if (chip->rhy & 0x02)
      OPL2_EnvelopeKeyOn(channel8->slotz[1], 2u);
    else
      OPL2_EnvelopeKeyOff(channel8->slotz[1], 2u);

    // Bit 2: Tom-Tom (Channel 8, Slot 1)
    if (chip->rhy & 0x04)
      OPL2_EnvelopeKeyOn(channel8->slotz[0], 2u);
    else
      OPL2_EnvelopeKeyOff(channel8->slotz[0], 2u);

    // Bit 3: Top Cymbal (Channel 7, Slot 2)
    if (chip->rhy & 0x08)
      OPL2_EnvelopeKeyOn(channel7->slotz[1], 2u);
    else
      OPL2_EnvelopeKeyOff(channel7->slotz[1], 2u);

    // Bit 4: Hi-Hat (Channel 6, Slots 1 & 2)
    if (chip->rhy & 0x10)
    {
      OPL2_EnvelopeKeyOn(channel6->slotz[0], 2u);
      OPL2_EnvelopeKeyOn(channel6->slotz[1], 2u);
    }
    else
    {
      OPL2_EnvelopeKeyOff(channel6->slotz[0], 2u);
      OPL2_EnvelopeKeyOff(channel6->slotz[1], 2u);
    }
  }
  else
  {
    // Rhythm mode disabled: reset channels 6-8 to normal melodic mode
    for (uint8_t i = 6; i < 9; ++i)
    {
      chip->channel[i].chtype = 0;
      OPL2_ChannelSetupCon(&chip->channel[i]);
      OPL2_EnvelopeKeyOff(chip->channel[i].slotz[0], 2u);
      OPL2_EnvelopeKeyOff(chip->channel[i].slotz[1], 2u);
    }
  }
}