void OPL3_ChannelUpdateAlg(opl3_channel *ch)
{
    // Initialize the algorithm based on the current connection mode
    ch->alg = ch->con;
    
    // Check if the chip is in new mode (non-zero newm value)
    if (ch->chip->newm == '\0') {
        // In old mode, setup the algorithm normally
        OPL3_ChannelSetupAlg(ch);
    }
    // Check if this is the first channel of a pair (chtype == 1)
    else if (ch->chtype == '\x01') {
        // Calculate algorithm for the pair channel based on connection modes
        // Bit 2 is set to 1 (value 4), and bits 0-1 are derived from pair's connection
        ch->pair->alg = ch->con << 1 | 4 | ch->pair->con;
        // Set this channel's algorithm to feedback mode (value 8, '\b')
        ch->alg = '\b';
        // Setup the algorithm for the pair channel
        OPL3_ChannelSetupAlg(ch->pair);
    }
    // Check if this is the second channel of a pair (chtype == 2)
    else if (ch->chtype == '\x02') {
        // Calculate algorithm for this channel based on pair's connection mode
        // Bit 2 is set to 1 (value 4), and bits 0-1 are derived from this channel's connection
        ch->alg = ch->pair->con << 1 | 4 | ch->con;
        // Set the pair channel's algorithm to feedback mode (value 8, '\b')
        ch->pair->alg = '\b';
        // Setup the algorithm for this channel
        OPL3_ChannelSetupAlg(ch);
    }
    else {
        // For other cases, setup the algorithm normally
        OPL3_ChannelSetupAlg(ch);
    }
}