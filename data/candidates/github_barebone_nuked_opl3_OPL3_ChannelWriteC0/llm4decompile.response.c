void OPL3_ChannelWriteC0(opl3_channel *channel, uint8_t data)
{
    channel->fb = (data & 0x0e) >> 1;
    channel->con = data & 0x01;
    OPL3_ChannelUpdateAlg(channel);
    if (channel->chip->newm)
    {
        channel->cha = (data & 0x10) ? 0xffff : 0x0000;
        channel->chb = (data & 0x20) ? 0xffff : 0x0000;
        channel->chc = (data & 0x40) ? 0xffff : 0x0000;
        channel->chd = (data & 0x80) ? 0xffff : 0x0000;
    }
    else
    {
        channel->cha = channel->chb = channel->chc = channel->chd = 0xffff;
    }
}