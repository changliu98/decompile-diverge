void opl3_set_mode(struct opl3_chip *chip, unsigned char mode)
{
  unsigned char i;
  for (i = 0; i < 6; i++)
  {
    unsigned char ch = i;
    if (ch >= 3)
      ch += 6;
    if (mode & (1 << i))
    {
      chip->channel[ch].chtype = 1;
      chip->channel[ch + 3].chtype = 2;
      opl3_set_chtype(&chip->channel[ch]);
    }
    else
    {
      chip->channel[ch].chtype = 0;
      chip->channel[ch + 3].chtype = 0;
      opl3_set_chtype(&chip->channel[ch]);
      opl3_set_chtype(&chip->channel[ch + 3]);
    }
  }
}