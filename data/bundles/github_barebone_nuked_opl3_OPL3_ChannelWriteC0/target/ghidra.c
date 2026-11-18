void OPL3_ChannelWriteC0(opl3_channel *channel,uint8_t data)

{
  uint16_t uVar1;
  uint8_t data_local;
  opl3_channel *channel_local;
  
  channel->fb = (uint8_t)((int)(data & 0xe) >> 1);
  channel->con = data & 1;
  OPL3_ChannelUpdateAlg(channel);
  if (channel->chip->newm == '\0') {
    channel->chb = 0xffff;
    channel->cha = 0xffff;
    channel->chd = 0;
    channel->chc = 0;
  }
  else {
    uVar1 = 0;
    if (((int)(uint)data >> 4 & 1U) != 0) {
      uVar1 = 0xffff;
    }
    channel->cha = uVar1;
    uVar1 = 0;
    if (((int)(uint)data >> 5 & 1U) != 0) {
      uVar1 = 0xffff;
    }
    channel->chb = uVar1;
    uVar1 = 0;
    if (((int)(uint)data >> 6 & 1U) != 0) {
      uVar1 = 0xffff;
    }
    channel->chc = uVar1;
    uVar1 = 0;
    if ((int)(uint)data >> 7 != 0) {
      uVar1 = 0xffff;
    }
    channel->chd = uVar1;
  }
  return;
}