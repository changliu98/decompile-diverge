static void OPL3_ChannelSet4Op(opl3_chip *chip, uint8_t data)
{
    uint8_t bit;
    uint8_t chnum;
    for (bit = 0; bit < 6; bit++)
    {
        chnum = bit;
        if (bit >= 3)
        {
            chnum += 9 - 3;
        }
        if ((data >> bit) & 0x01)
        {
            chip->channel[chnum].chtype = ch_4op;
            chip->channel[chnum + 3u].chtype = ch_4op2;
            OPL3_ChannelUpdateAlg(&chip->channel[chnum]);
        }
        else
        {
            chip->channel[chnum].chtype = ch_2op;
            chip->channel[chnum + 3u].chtype = ch_2op;
            OPL3_ChannelUpdateAlg(&chip->channel[chnum]);
            OPL3_ChannelUpdateAlg(&chip->channel[chnum + 3u]);
        }
    }
}