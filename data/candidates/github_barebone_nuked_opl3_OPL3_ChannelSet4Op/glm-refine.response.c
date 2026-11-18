void __cdecl OPL3_ChannelSet4Op(opl3_chip *chip, uint8_t data)
{
  uint8_t base_chnum;

  // Iterate over the 6 possible 4-operator channel pairs
  for (uint8_t pair = 0; pair < 6; ++pair)
  {
    // The first 3 pairs are at indices 0-2, the next 3 are at indices 6-8
    base_chnum = (pair < 3) ? pair : pair + 6;

    bool is_4op = (data >> pair) & 1;

    if (is_4op)
    {
      // Pair the channels: base channel acts as the primary (1), 
      // and the channel 3 slots ahead acts as the secondary (2)
      chip->channel[base_chnum].chtype = 1;
      chip->channel[base_chnum + 3].chtype = 2;
      
      OPL3_ChannelUpdateAlg(&chip->channel[base_chnum]);
    }
    else
    {
      // Unpair the channels: reset both to standard 2-operator mode (0)
      chip->channel[base_chnum].chtype = 0;
      chip->channel[base_chnum + 3].chtype = 0;
      
      OPL3_ChannelUpdateAlg(&chip->channel[base_chnum]);
      OPL3_ChannelUpdateAlg(&chip->channel[base_chnum + 3]);
    }
  }
}