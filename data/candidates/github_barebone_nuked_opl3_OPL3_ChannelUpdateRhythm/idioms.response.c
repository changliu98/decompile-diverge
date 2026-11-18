void OPL3_ChannelUpdateRhythm(struct opl3_chip *chip, unsigned char val)
{
  struct opl3_channel *ch;
  unsigned char i;
  chip->rhy = val & 0x3f;
  if (chip->rhy & 0x20)
  {
    ch = &chip->channel[6];
    ch = &chip->channel[7];
    ch = &chip->channel[8];
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
    for (i = 6; i < 9; i++)
      chip->channel[i].chtype = 3;
    opl3_set_chtype(ch);
    opl3_set_chtype(ch);
    opl3_set_chtype(ch);
    if (chip->rhy & 1)
      opl3_set_slottype(chip->channel[7].slotz[0], 2);
    else
      opl3_set_slottype_noise(chip->channel[7].slotz[0], 2);
    if (chip->rhy & 2)
      opl3_set_slottype(chip->channel[8].slotz[1], 2);
    else
      opl3_set_slottype_noise(chip->channel[8].slotz[1], 2);
    if (chip->rhy & 4)
      opl3_set_slottype(chip->channel[8].slotz[0], 2);
    else
      opl3_set_slottype_noise(chip->channel[8].slotz[0], 2);
    if (chip->rhy & 8)
      opl3_set_slottype(chip->channel[7].slotz[1], 2);
    else
      opl3_set_slottype_noise(chip->channel[7].slotz[1], 2);
    if (chip->rhy & 0x10)
    {
      opl3_set_slottype(chip->channel[6].slotz[0], 2);
      opl3_set_slottype(chip->channel[6].slotz[1], 2);
    }
    else
    {
      opl3_set_slottype_noise(chip->channel[6].slotz[0], 2);
      opl3_set_slottype_noise(chip->channel[6].slotz[1], 2);
    }
  }
  else
  {
    for (i = 6; i < 9; i++)
    {
      chip->channel[i].chtype = 0;
      opl3_set_chtype(&chip->channel[i]);
      opl3_set_slottype_noise(chip->channel[i].slotz[0], 2);
      opl3_set_slottype_noise(chip->channel[i].slotz[1], 2);
    }
  }
}