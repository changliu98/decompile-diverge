void __cdecl OPL3_ChannelUpdateAlg(opl3_channel *channel)
{
  channel->alg = channel->con;
  if ( channel->chip->newm )
  {
    if ( channel->chtype == 1 )
    {
      channel->pair->alg = channel->pair->con | (2 * channel->con) | 4;
      channel->alg = 8;
      OPL3_ChannelSetupAlg(channel->pair);
      return;
    }
    if ( channel->chtype == 2 )
    {
      channel->alg = channel->con | (2 * channel->pair->con) | 4;
      channel->pair->alg = 8;
    }
  }
  OPL3_ChannelSetupAlg(channel);
}