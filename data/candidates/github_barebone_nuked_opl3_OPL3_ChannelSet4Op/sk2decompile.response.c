static void OPL3_ChannelSet4Op(opl3_chip *chip, unsigned int mask) {
  unsigned int i;
  unsigned int chan;
  for (i = 0; i < 6; i++) {
    chan = i;
    if (i >= 3) {
      chan += 6;
    }
    if (mask & (1 << i)) {
      chip->channel[chan].type = 1;
      chip->channel[chan + 3].type = 2;
      OPL3_ChannelUpdateAlg(&chip->channel[chan]);
    } else {
      chip->channel[chan].type = 0;
      chip->channel[chan + 3].type = 0;
      OPL3_ChannelUpdateAlg(&chip->channel[chan]);
      OPL3_ChannelUpdateAlg(&chip->channel[chan + 3]);
    }
  }
}