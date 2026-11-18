void __cdecl OPL3_ChannelUpdateRhythm(opl3_chip *chip, uint8_t data)
{
  uint8_t chnum; // [rsp+7h] [rbp-29h]
  uint8_t chnuma; // [rsp+7h] [rbp-29h]
  opl3_channel *channel8; // [rsp+8h] [rbp-28h]
  opl3_channel *channel7; // [rsp+10h] [rbp-20h]
  opl3_channel *channel6; // [rsp+18h] [rbp-18h]

  chip->rhy = data & 0x3F;
  if ( (chip->rhy & 0x20) != 0 )
  {
    channel6 = &chip->channel[6];
    channel7 = &chip->channel[7];
    channel8 = &chip->channel[8];
    chip->channel[6].out[0] = &chip->channel[6].slotz[1]->out;
    chip->channel[6].out[1] = &chip->channel[6].slotz[1]->out;
    chip->channel[6].out[2] = &chip->zeromod;
    chip->channel[6].out[3] = &chip->zeromod;
    chip->channel[7].out[0] = &chip->channel[7].slotz[0]->out;
    chip->channel[7].out[1] = &chip->channel[7].slotz[0]->out;
    chip->channel[7].out[2] = &chip->channel[7].slotz[1]->out;
    chip->channel[7].out[3] = &chip->channel[7].slotz[1]->out;
    chip->channel[8].out[0] = &chip->channel[8].slotz[0]->out;
    chip->channel[8].out[1] = &chip->channel[8].slotz[0]->out;
    chip->channel[8].out[2] = &chip->channel[8].slotz[1]->out;
    chip->channel[8].out[3] = &chip->channel[8].slotz[1]->out;
    for ( chnum = 6; chnum < 9u; ++chnum )
      chip->channel[chnum].chtype = 3;
    OPL3_ChannelSetupAlg(channel6);
    OPL3_ChannelSetupAlg(channel7);
    OPL3_ChannelSetupAlg(channel8);
    if ( (chip->rhy & 1) != 0 )
      OPL3_EnvelopeKeyOn(channel7->slotz[0], 2u);
    else
      OPL3_EnvelopeKeyOff(channel7->slotz[0], 2u);
    if ( (chip->rhy & 2) != 0 )
      OPL3_EnvelopeKeyOn(chip->channel[8].slotz[1], 2u);
    else
      OPL3_EnvelopeKeyOff(chip->channel[8].slotz[1], 2u);
    if ( (chip->rhy & 4) != 0 )
      OPL3_EnvelopeKeyOn(channel8->slotz[0], 2u);
    else
      OPL3_EnvelopeKeyOff(channel8->slotz[0], 2u);
    if ( (chip->rhy & 8) != 0 )
      OPL3_EnvelopeKeyOn(chip->channel[7].slotz[1], 2u);
    else
      OPL3_EnvelopeKeyOff(chip->channel[7].slotz[1], 2u);
    if ( (chip->rhy & 0x10) != 0 )
    {
      OPL3_EnvelopeKeyOn(channel6->slotz[0], 2u);
      OPL3_EnvelopeKeyOn(chip->channel[6].slotz[1], 2u);
    }
    else
    {
      OPL3_EnvelopeKeyOff(channel6->slotz[0], 2u);
      OPL3_EnvelopeKeyOff(chip->channel[6].slotz[1], 2u);
    }
  }
  else
  {
    for ( chnuma = 6; chnuma < 9u; ++chnuma )
    {
      chip->channel[chnuma].chtype = 0;
      OPL3_ChannelSetupAlg(&chip->channel[chnuma]);
      OPL3_EnvelopeKeyOff(chip->channel[chnuma].slotz[0], 2u);
      OPL3_EnvelopeKeyOff(chip->channel[chnuma].slotz[1], 2u);
    }
  }
}