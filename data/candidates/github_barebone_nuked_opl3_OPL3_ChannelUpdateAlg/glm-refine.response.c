void __cdecl OPL3_ChannelUpdateAlg(opl3_channel *channel)
{
    // Default the algorithm to the channel's own connection setting
    channel->alg = channel->con;

    // Check if the chip is in OPL3 (new) mode
    if (channel->chip->newm) 
    {
        if (channel->chtype == 1) 
        {
            // Type 1: This channel acts as the secondary operator in a 4-op pair
            opl3_channel *pair = channel->pair;
            pair->alg = combine_alg(channel->con, pair->con);
            channel->alg = 8;
            OPL3_ChannelSetupAlg(pair);
            return;
        }
        
        if (channel->chtype == 2) 
        {
            // Type 2: This channel acts as the primary operator in a 4-op pair
            opl3_channel *pair = channel->pair;
            channel->alg = combine_alg(pair->con, channel->con);
            pair->alg = 8;
        }
    }
    
    // Fallthrough for non-OPL3 mode, or if chtype == 2
    OPL3_ChannelSetupAlg(channel);
}