static void OPL3_ChannelUpdateAlg(opl3_channel *channel)
{
    channel->alg = channel->con;
    if (channel->chip->newm)
    {
        if (channel->chtype == ch_4op)
        {
            channel->pair->alg = 0x04 | (channel->con << 1) | (channel->pair->con);
            channel->alg = 0x08;
            OPL3_ChannelSetupAlg(channel->pair);
        }
        else if (channel->chtype == ch_4op2)
        {
            channel->alg = 0x04 | (channel->pair->con << 1) | (channel->con);
            channel->pair->alg = 0x08;
            OPL3_ChannelSetupAlg(channel);
        }
        else
        {
            OPL3_ChannelSetupAlg(channel);
        }
    }
    else
    {
        OPL3_ChannelSetupAlg(channel);
    }
}