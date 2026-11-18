void OPL3_ChannelSet4Op(opl3_chip *chip,uint8_t data)

{
  uint8_t chnum;
  uint8_t bit;
  uint8_t data_local;
  opl3_chip *chip_local;
  
  for (bit = '\0'; bit < 6; bit = bit + '\x01') {
    chnum = bit;
    if (2 < bit) {
      chnum = bit + '\x06';
    }
    if (((int)(uint)data >> (bit & 0x1f) & 1U) == 0) {
      chip->channel[chnum].chtype = '\0';
      chip->channel[chnum + 3].chtype = '\0';
      OPL3_ChannelUpdateAlg(chip->channel + chnum);
      OPL3_ChannelUpdateAlg(chip->channel + (chnum + 3));
    }
    else {
      chip->channel[chnum].chtype = '\x01';
      chip->channel[chnum + 3].chtype = '\x02';
      OPL3_ChannelUpdateAlg(chip->channel + chnum);
    }
  }
  return;
}