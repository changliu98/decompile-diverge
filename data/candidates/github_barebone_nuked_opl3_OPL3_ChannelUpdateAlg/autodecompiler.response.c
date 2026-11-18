void OPL3_ChannelUpdateAlg(opl3_channel *channel)
{
    channel->cha = channel->chsl1[0x46];

    if (channel->slotz[0x46])
    {
        if (channel->chtype == 1)
        {
            channel->chsl1[0x47] = 0x04 | (channel->cha << 1) | channel->chsl1[0x46];
            channel->cha = 0x08;
            OPL3_ChannelSetupAlg(channel->chsl1);
        }
        else if (channel->chtype == 2)
        {
            channel->cha = 0x04 | (channel->chsl1[0x46] << 1) | channel->cha;
            channel->chsl1[0x47] = 0x08;
            OPL3_ChannelSetupAlg(channel);
        }
        else
        {
            OPL3_ChannelSetupAlg(channel);
        }
        return;
    }

    OPL3_ChannelSetupAlg(channel);
}