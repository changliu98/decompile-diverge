void OPL3_ChannelUpdateRhythm(opl3_chip *chip,uint8_t data)

{
  opl3_channel *channel;
  opl3_channel *channel_00;
  opl3_channel *channel_01;
  uint8_t chnum;
  opl3_channel *channel8;
  opl3_channel *channel7;
  opl3_channel *channel6;
  uint8_t data_local;
  opl3_chip *chip_local;
  
  chip->rhy = data & 0x3f;
  if ((chip->rhy & 0x20) == 0) {
    for (chnum = '\x06'; chnum < 9; chnum = chnum + '\x01') {
      chip->channel[chnum].chtype = '\0';
      OPL3_ChannelSetupAlg(chip->channel + chnum);
      OPL3_EnvelopeKeyOff(chip->channel[chnum].slotz[0],'\x02');
      OPL3_EnvelopeKeyOff(chip->channel[chnum].slotz[1],'\x02');
    }
  }
  else {
    channel = chip->channel + 6;
    channel_00 = chip->channel + 7;
    channel_01 = chip->channel + 8;
    chip->channel[6].out[0] = &chip->channel[6].slotz[1]->out;
    chip->channel[6].out[1] = &chip->channel[6].slotz[1]->out;
    chip->channel[6].out[2] = &chip->zeromod;
    chip->channel[6].out[3] = &chip->zeromod;
    chip->channel[7].out[0] = &channel_00->slotz[0]->out;
    chip->channel[7].out[1] = &channel_00->slotz[0]->out;
    chip->channel[7].out[2] = &chip->channel[7].slotz[1]->out;
    chip->channel[7].out[3] = &chip->channel[7].slotz[1]->out;
    chip->channel[8].out[0] = &channel_01->slotz[0]->out;
    chip->channel[8].out[1] = &channel_01->slotz[0]->out;
    chip->channel[8].out[2] = &chip->channel[8].slotz[1]->out;
    chip->channel[8].out[3] = &chip->channel[8].slotz[1]->out;
    for (chnum = '\x06'; chnum < 9; chnum = chnum + '\x01') {
      chip->channel[chnum].chtype = '\x03';
    }
    OPL3_ChannelSetupAlg(channel);
    OPL3_ChannelSetupAlg(channel_00);
    OPL3_ChannelSetupAlg(channel_01);
    if ((chip->rhy & 1) == 0) {
      OPL3_EnvelopeKeyOff(channel_00->slotz[0],'\x02');
    }
    else {
      OPL3_EnvelopeKeyOn(channel_00->slotz[0],'\x02');
    }
    if ((chip->rhy & 2) == 0) {
      OPL3_EnvelopeKeyOff(chip->channel[8].slotz[1],'\x02');
    }
    else {
      OPL3_EnvelopeKeyOn(chip->channel[8].slotz[1],'\x02');
    }
    if ((chip->rhy & 4) == 0) {
      OPL3_EnvelopeKeyOff(channel_01->slotz[0],'\x02');
    }
    else {
      OPL3_EnvelopeKeyOn(channel_01->slotz[0],'\x02');
    }
    if ((chip->rhy & 8) == 0) {
      OPL3_EnvelopeKeyOff(chip->channel[7].slotz[1],'\x02');
    }
    else {
      OPL3_EnvelopeKeyOn(chip->channel[7].slotz[1],'\x02');
    }
    if ((chip->rhy & 0x10) == 0) {
      OPL3_EnvelopeKeyOff(channel->slotz[0],'\x02');
      OPL3_EnvelopeKeyOff(chip->channel[6].slotz[1],'\x02');
    }
    else {
      OPL3_EnvelopeKeyOn(channel->slotz[0],'\x02');
      OPL3_EnvelopeKeyOn(chip->channel[6].slotz[1],'\x02');
    }
  }
  return;
}