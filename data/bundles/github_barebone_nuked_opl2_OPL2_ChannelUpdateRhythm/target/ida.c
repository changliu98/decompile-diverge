void __cdecl OPL2_ChannelUpdateRhythm(opl2_chip *chip, uint8_t data)
{
  uint8_t chnum; // [rsp+7h] [rbp-29h]
  uint8_t chnuma; // [rsp+7h] [rbp-29h]
  opl2_channel *channel8; // [rsp+8h] [rbp-28h]
  opl2_channel *channel7; // [rsp+10h] [rbp-20h]
  opl2_channel *channel6; // [rsp+18h] [rbp-18h]

  chip->rhy = data & 0x3F;
  if ( (chip->rhy & 0x20) != 0 )
  {
    channel6 = &chip->channel[6];
    channel7 = &chip->channel[7];
    channel8 = &chip->channel[8];
    for ( chnum = 6; chnum < 9u; ++chnum )
      chip->channel[chnum].chtype = 1;
    OPL2_ChannelSetupCon(channel6);
    OPL2_ChannelSetupCon(channel7);
    OPL2_ChannelSetupCon(channel8);
    if ( (chip->rhy & 1) != 0 )
      OPL2_EnvelopeKeyOn(channel7->slotz[0], 2u);
    else
      OPL2_EnvelopeKeyOff(channel7->slotz[0], 2u);
    if ( (chip->rhy & 2) != 0 )
      OPL2_EnvelopeKeyOn(chip->channel[8].slotz[1], 2u);
    else
      OPL2_EnvelopeKeyOff(chip->channel[8].slotz[1], 2u);
    if ( (chip->rhy & 4) != 0 )
      OPL2_EnvelopeKeyOn(channel8->slotz[0], 2u);
    else
      OPL2_EnvelopeKeyOff(channel8->slotz[0], 2u);
    if ( (chip->rhy & 8) != 0 )
      OPL2_EnvelopeKeyOn(chip->channel[7].slotz[1], 2u);
    else
      OPL2_EnvelopeKeyOff(chip->channel[7].slotz[1], 2u);
    if ( (chip->rhy & 0x10) != 0 )
    {
      OPL2_EnvelopeKeyOn(channel6->slotz[0], 2u);
      OPL2_EnvelopeKeyOn(chip->channel[6].slotz[1], 2u);
    }
    else
    {
      OPL2_EnvelopeKeyOff(channel6->slotz[0], 2u);
      OPL2_EnvelopeKeyOff(chip->channel[6].slotz[1], 2u);
    }
  }
  else
  {
    for ( chnuma = 6; chnuma < 9u; ++chnuma )
    {
      chip->channel[chnuma].chtype = 0;
      OPL2_ChannelSetupCon(&chip->channel[chnuma]);
      OPL2_EnvelopeKeyOff(chip->channel[chnuma].slotz[0], 2u);
      OPL2_EnvelopeKeyOff(chip->channel[chnuma].slotz[1], 2u);
    }
  }
}