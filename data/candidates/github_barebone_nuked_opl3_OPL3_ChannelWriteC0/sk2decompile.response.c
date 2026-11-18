static void OPL3_ChannelWriteC0(opl3_channel *channel, Bit8u data) {
  channel->slot = (data & 0x0e) >> 1;
  channel->keyon = data & 0x01;
  OPL3_ChannelUpdateAlg(channel);
  if (channel->chip->newm) {
    channel->eg_out_mask_a = (data & 0x10) ? 0xffff : 0;
    channel->eg_out_mask_b = (data & 0x20) ? 0xffff : 0;
    channel->eg_out_mask_c = (data & 0x40) ? 0xffff : 0;
    channel->eg_out_mask_d = (data & 0x80) ? 0xffff : 0;
  } else {
    channel->eg_out_mask_a = channel->eg_out_mask_b = 0xffff;
    channel->eg_out_mask_c = channel->eg_out_mask_d = 0;
  }
}