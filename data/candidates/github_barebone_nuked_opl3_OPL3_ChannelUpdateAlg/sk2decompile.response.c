static void OPL3_ChannelUpdateAlg(opl3_channel *channel) {
  channel->connection = channel->chipout;
  if (channel->chip->routing) {
    if (channel->chtype == 1) {
      channel->pair->connection = channel->chipout | (channel->chipout << 1) | 4;
      channel->connection = 8;
      OPL3_ChannelSetupAlg(channel->pair);
      return;
    }
    if (channel->chtype == 2) {
      channel->connection = channel->chipout | (channel->pair->chipout << 1) | 4;
      channel->pair->connection = 8;
    }
  }
  OPL3_ChannelSetupAlg(channel);
}