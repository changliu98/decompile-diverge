void OPL3_ChannelSet4Op(opl3_chip *chip, uint8_t data)
{
    uint8_t i;
    uint8_t chnum;

    for (i = 0; i < 6; i++)
    {
        chnum = i;
        if (i >= 3)
        {
            chnum += 3;
        }
        if (data & (1 << i))
        {
            chip->channel[chnum].chtype = 1;
            chip->channel[chnum + 3].chtype = 2;
            OPL3_ChannelUpdateAlg(&chip->channel[chnum]);
        }
        else
        {
            chip->channel[chnum].chtype = 0;
            chip->channel[chnum + 3].chtype = 0;
            OPL3_ChannelUpdateAlg(&chip->channel[chnum]);
            OPL3_ChannelUpdateAlg(&chip->channel[chnum + 3]);
        }
    }
}