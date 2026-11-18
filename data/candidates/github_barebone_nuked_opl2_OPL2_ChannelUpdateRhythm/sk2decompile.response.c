static void OPL2_ChannelUpdateRhythm(OPL2 *chip, unsigned char data) {
  unsigned char i;
  chip->rhythm = data & 0x3f;
  if (chip->rhythm & 0x20) {
    OPL2_CHANNEL *channel6 = &chip->channel[6];
    OPL2_CHANNEL *channel7 = &chip->channel[7];
    OPL2_CHANNEL *channel8 = &chip->channel[8];
    for (i = 6; i < 9; i++) {
      chip->channel[i].rhythm_flag = 1;
    }
    OPL2_ChannelSetupCon(channel6);
    OPL2_ChannelSetupCon(channel7);
    OPL2_ChannelSetupCon(channel8);
    if (chip->rhythm & 0x01) {
      OPL2_EnvelopeKeyOn(channel7->slot1, 2);
    } else {
      OPL2_EnvelopeKeyOff(channel7->slot1, 2);
    }
    if (chip->rhythm & 0x02) {
      OPL2_EnvelopeKeyOn(channel8->slot2, 2);
    } else {
      OPL2_EnvelopeKeyOff(channel8->slot2, 2);
    }
    if (chip->rhythm & 0x04) {
      OPL2_EnvelopeKeyOn(channel8->slot1, 2);
    } else {
      OPL2_EnvelopeKeyOff(channel8->slot1, 2);
    }
    if (chip->rhythm & 0x08) {
      OPL2_EnvelopeKeyOn(channel7->slot2, 2);
    } else {
      OPL2_EnvelopeKeyOff(channel7->slot2, 2);
    }
    if (chip->rhythm & 0x10) {
      OPL2_EnvelopeKeyOn(channel6->slot1, 2);
      OPL2_EnvelopeKeyOn(channel6->slot2, 2);
    } else {
      OPL2_EnvelopeKeyOff(channel6->slot1, 2);
      OPL2_EnvelopeKeyOff(channel6->slot2, 2);
    }
  } else {
    for (i = 6; i < 9; i++) {
      chip->channel[i].rhythm_flag = 0;
      OPL2_ChannelSetupCon(&chip->channel[i]);
      OPL2_EnvelopeKeyOff(chip->channel[i].slot1, 2);
      OPL2_EnvelopeKeyOff(chip->channel[i].slot2, 2);
    }
  }
}