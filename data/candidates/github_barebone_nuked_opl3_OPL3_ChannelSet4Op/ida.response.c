void __cdecl OPL3_ChannelSet4Op(opl3_chip *chip, uint8_t data)
{
  uint8_t chnum; // [rsp+5h] [rbp-Bh]
  uint8_t bit; // [rsp+6h] [rbp-Ah]

  for ( bit = 0; bit < 6u; ++bit )
  {
    chnum = bit;
    if ( bit >= 3u )
      chnum = bit + 6;
    if ( (((int)data >> bit) & 1) != 0 )
    {
      chip->channel[chnum].chtype = 1;
      chip->channel[(unsigned int)chnum + 3].chtype = 2;
      OPL3_ChannelUpdateAlg(&chip->channel[chnum]);
    }
    else
    {
      chip->channel[chnum].chtype = 0;
      chip->channel[(unsigned int)chnum + 3].chtype = 0;
      OPL3_ChannelUpdateAlg(&chip->channel[chnum]);
      OPL3_ChannelUpdateAlg(&chip->channel[(unsigned int)chnum + 3]);
    }
  }
}