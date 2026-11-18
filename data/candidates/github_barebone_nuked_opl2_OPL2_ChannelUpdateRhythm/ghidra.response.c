void OPL2_ChannelUpdateRhythm(opl2_chip *chip,uint8_t data)

{
  opl2_channel *channel;
  opl2_channel *channel_00;
  opl2_channel *channel_01;
  uint8_t chnum;
  opl2_channel *channel8;
  opl2_channel *channel7;
  opl2_channel *channel6;
  uint8_t data_local;
  opl2_chip *chip_local;
  
  chip->rhy = data & 0x3f;
  if ((chip->rhy & 0x20) == 0) {
    for (chnum = '\x06'; chnum < 9; chnum = chnum + '\x01') {
      chip->channel[chnum].chtype = '\0';
      OPL2_ChannelSetupCon(chip->channel + chnum);
      OPL2_EnvelopeKeyOff(chip->channel[chnum].slotz[0],'\x02');
      OPL2_EnvelopeKeyOff(chip->channel[chnum].slotz[1],'\x02');
    }
  }
  else {
    channel = chip->channel + 6;
    channel_00 = chip->channel + 7;
    channel_01 = chip->channel + 8;
    for (chnum = '\x06'; chnum < 9; chnum = chnum + '\x01') {
      chip->channel[chnum].chtype = '\x01';
    }
    OPL2_ChannelSetupCon(channel);
    OPL2_ChannelSetupCon(channel_00);
    OPL2_ChannelSetupCon(channel_01);
    if ((chip->rhy & 1) == 0) {
      OPL2_EnvelopeKeyOff(channel_00->slotz[0],'\x02');
    }
    else {
      OPL2_EnvelopeKeyOn(channel_00->slotz[0],'\x02');
    }
    if ((chip->rhy & 2) == 0) {
      OPL2_EnvelopeKeyOff(chip->channel[8].slotz[1],'\x02');
    }
    else {
      OPL2_EnvelopeKeyOn(chip->channel[8].slotz[1],'\x02');
    }
    if ((chip->rhy & 4) == 0) {
      OPL2_EnvelopeKeyOff(channel_01->slotz[0],'\x02');
    }
    else {
      OPL2_EnvelopeKeyOn(channel_01->slotz[0],'\x02');
    }
    if ((chip->rhy & 8) == 0) {
      OPL2_EnvelopeKeyOff(chip->channel[7].slotz[1],'\x02');
    }
    else {
      OPL2_EnvelopeKeyOn(chip->channel[7].slotz[1],'\x02');
    }
    if ((chip->rhy & 0x10) == 0) {
      OPL2_EnvelopeKeyOff(channel->slotz[0],'\x02');
      OPL2_EnvelopeKeyOff(chip->channel[6].slotz[1],'\x02');
    }
    else {
      OPL2_EnvelopeKeyOn(channel->slotz[0],'\x02');
      OPL2_EnvelopeKeyOn(chip->channel[6].slotz[1],'\x02');
    }
  }
  return;
}