void OPL2_ChannelUpdateRhythm(struct opl2_chip *chip, unsigned char rythm)
{
  struct opl2_channel *ch;
  unsigned char i;
  chip->rhy = rythm & 0x3f;
  if (chip->rhy & 0x20)
  {
    ch = &chip->channel[6];
    ch = &chip->channel[7];
    ch = &chip->channel[8];
    for (i = 6; i < 9; i++)
      chip->channel[i].chtype = 1;
    OPL2_ChannelSetupCon(ch);
    OPL2_ChannelSetupCon(ch);
    OPL2_ChannelSetupCon(ch);
    if (chip->rhy & 1)
      OPL2_EnvelopeKeyOn(chip->channel[7].slotz[0], 2);
    else
      OPL2_EnvelopeKeyOff(chip->channel[7].slotz[0], 2);
    if (chip->rhy & 2)
      OPL2_EnvelopeKeyOn(chip->channel[8].slotz[1], 2);
    else
      OPL2_EnvelopeKeyOff(chip->channel[8].slotz[1], 2);
    if (chip->rhy & 4)
      OPL2_EnvelopeKeyOn(chip->channel[8].slotz[0], 2);
    else
      OPL2_EnvelopeKeyOff(chip->channel[8].slotz[0], 2);
    if (chip->rhy & 8)
      OPL2_EnvelopeKeyOn(chip->channel[7].slotz[1], 2);
    else
      OPL2_EnvelopeKeyOff(chip->channel[7].slotz[1], 2);
    if (chip->rhy & 16)
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
    for (i = 6; i < 9; i++)
    {
      chip->channel[i].chtype = 0;
      ch = &chip->channel[i];
      OPL2_ChannelSetupCon(ch);
      OPL2_EnvelopeKeyOff(chip->channel[i].slotz[0], 2);
      OPL2_EnvelopeKeyOff(chip->channel[i].slotz[1], 2);
    }
  }
}