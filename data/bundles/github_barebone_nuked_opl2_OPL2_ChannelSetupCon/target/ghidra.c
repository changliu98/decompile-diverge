void OPL2_ChannelSetupCon(opl2_channel *channel)

{
  opl2_channel *channel_local;
  
  if (channel->chtype == '\x01') {
    if ((channel->ch_num == '\a') || (channel->ch_num == '\b')) {
      channel->slotz[0]->mod = &channel->chip->zeromod;
      channel->slotz[1]->mod = &channel->chip->zeromod;
    }
    else if (channel->con == '\0') {
      channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
      channel->slotz[1]->mod = &channel->slotz[0]->out;
    }
    else if (channel->con == '\x01') {
      channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
      channel->slotz[1]->mod = &channel->chip->zeromod;
    }
  }
  else if (channel->con == '\0') {
    channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
    channel->slotz[1]->mod = &channel->slotz[0]->out;
  }
  else if (channel->con == '\x01') {
    channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
    channel->slotz[1]->mod = &channel->chip->zeromod;
  }
  return;
}