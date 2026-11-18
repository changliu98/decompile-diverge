void __cdecl OPL3_ChannelWriteC0(opl3_channel *channel, uint8_t data)
{
  uint16_t v2; // ax
  uint16_t v3; // ax
  uint16_t v4; // ax
  uint16_t v5; // ax

  channel->fb = (data & 0xE) >> 1;
  channel->con = data & 1;
  OPL3_ChannelUpdateAlg(channel);
  if ( channel->chip->newm )
  {
    v2 = 0;
    if ( (((int)data >> 4) & 1) != 0 )
      v2 = -1;
    channel->cha = v2;
    v3 = 0;
    if ( (((int)data >> 5) & 1) != 0 )
      v3 = -1;
    channel->chb = v3;
    v4 = 0;
    if ( (((int)data >> 6) & 1) != 0 )
      v4 = -1;
    channel->chc = v4;
    v5 = 0;
    if ( (((int)data >> 7) & 1) != 0 )
      v5 = -1;
    channel->chd = v5;
  }
  else
  {
    channel->chb = -1;
    channel->cha = -1;
    channel->chd = 0;
    channel->chc = 0;
  }
}