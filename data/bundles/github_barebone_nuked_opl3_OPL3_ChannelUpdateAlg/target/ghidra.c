void OPL3_ChannelUpdateAlg(opl3_channel *channel)

{
  opl3_channel *channel_local;
  
  channel->alg = channel->con;
  if (channel->chip->newm == '\0') {
    OPL3_ChannelSetupAlg(channel);
  }
  else if (channel->chtype == '\x01') {
    channel->pair->alg = channel->con << 1 | 4 | channel->pair->con;
    channel->alg = '\b';
    OPL3_ChannelSetupAlg(channel->pair);
  }
  else if (channel->chtype == '\x02') {
    channel->alg = channel->pair->con << 1 | 4 | channel->con;
    channel->pair->alg = '\b';
    OPL3_ChannelSetupAlg(channel);
  }
  else {
    OPL3_ChannelSetupAlg(channel);
  }
  return;
}