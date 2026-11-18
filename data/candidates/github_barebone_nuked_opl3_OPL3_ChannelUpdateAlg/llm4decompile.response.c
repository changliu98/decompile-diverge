void OPL3_ChannelUpdateAlg(opl3_channel *channel)
{
    channel->alg = channel->con;
    if (channel->chip->newm)
    {
        if (channel->chtype == 1)
        {
            channel->pair->alg = (channel->pair->con << 1) | 4 | channel->con;
            channel->alg = 8;
            OPL3_ChannelSetupAlg(channel->pair);
        }
        else if (channel->chtype == 2)
        {
            channel->alg = (channel->pair->con << 1) | 4 | channel->con;
            channel->pair->alg = 8;
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