void __cdecl OPL3_ChannelWriteC0(opl3_channel *channel, uint8_t data)
{
  // Bits 1-3: Feedback (FB)
  channel->fb = (data >> 1) & 0x07;
  
  // Bit 0: Connection (CON)
  channel->con = data & 1;
  
  OPL3_ChannelUpdateAlg(channel);

  if (channel->chip->newm)
  {
    // Bits 4-7 control channel output routing in OPL3 mode
    channel->cha = (data >> 4) & 1 ? 0xFFFF : 0;
    channel->chb = (data >> 5) & 1 ? 0xFFFF : 0;
    channel->chc = (data >> 6) & 1 ? 0xFFFF : 0;
    channel->chd = (data >> 7) & 1 ? 0xFFFF : 0;
  }
  else
  {
    // OPL2 mode fallback: route to channels A and B
    channel->cha = 0xFFFF;
    channel->chb = 0xFFFF;
    channel->chc = 0;
    channel->chd = 0;
  }
}