static void OPL3_ChannelUpdateRhythm(opl3_chip *chip, unsigned char data) {
  unsigned char i;
  chip->rhythm = data & 0x3f;
  if (chip->rhythm & 0x20) {
    opl3_channel *c6 = &chip->channel[6];
    opl3_channel *c7 = &chip->channel[7];
    opl3_channel *c8 = &chip->channel[8];
    c6->slot_output[0] = &c6->slot[1].output;
    c6->slot_output[1] = &c6->slot[1].output;
    c6->slot_output[2] = &chip->noise_output;
    c6->slot_output[3] = &chip->noise_output;
    c7->slot_output[0] = &c7->slot[0].output;
    c7->slot_output[1] = &c7->slot[0].output;
    c7->slot_output[2] = &c7->slot[1].output;
    c7->slot_output[3] = &c7->slot[1].output;
    c8->slot_output[0] = &c8->slot[0].output;
    c8->slot_output[1] = &c8->slot[0].output;
    c8->slot_output[2] = &c8->slot[1].output;
    c8->slot_output[3] = &c8->slot[1].output;
    for (i = 6; i < 9; i++) {
      chip->channel[i].rhythm_mask = 3;
    }
    OPL3_ChannelSetupAlg(c6);
    OPL3_ChannelSetupAlg(c7);
    OPL3_ChannelSetupAlg(c8);
    if (chip->rhythm & 1) {
      OPL3_EnvelopeKeyOn(c7->slot[0].state, 2);
    } else {
      OPL3_EnvelopeKeyOff(c7->slot[0].state, 2);
    }
    if (chip->rhythm & 2) {
      OPL3_EnvelopeKeyOn(c8->slot[1].state, 2);
    } else {
      OPL3_EnvelopeKeyOff(c8->slot[1].state, 2);
    }
    if (chip->rhythm & 4) {
      OPL3_EnvelopeKeyOn(c8->slot[0].state, 2);
    } else {
      OPL3_EnvelopeKeyOff(c8->slot[0].state, 2);
    }
    if (chip->rhythm & 8) {
      OPL3_EnvelopeKeyOn(c7->slot[1].state, 2);
    } else {
      OPL3_EnvelopeKeyOff(c7->slot[1].state, 2);
    }
    if (chip->rhythm & 0x10) {
      OPL3_EnvelopeKeyOn(c6->slot[0].state, 2);
      OPL3_EnvelopeKeyOn(c6->slot[1].state, 2);
    } else {
      OPL3_EnvelopeKeyOff(c6->slot[0].state, 2);
      OPL3_EnvelopeKeyOff(c6->slot[1].state, 2);
    }
  } else {
    for (i = 6; i < 9; i++) {
      chip->channel[i].rhythm_mask = 0;
      OPL3_ChannelSetupAlg(&chip->channel[i]);
      OPL3_EnvelopeKeyOff(chip->channel[i].slot[0].state, 2);
      OPL3_EnvelopeKeyOff(chip->channel[i].slot[1].state, 2);
    }
  }
}