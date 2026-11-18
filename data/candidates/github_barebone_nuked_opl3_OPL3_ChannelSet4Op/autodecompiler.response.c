void OPL3_ChannelSet4Op(opl3_chip *chip, Bit8u data)
{
    unsigned char slotnum;
    unsigned char chnum;
    unsigned char i;

    for (i = 0; i < 7; i++)
    {
        if (i < 4)
        {
            chnum = i;
        }
        else
        {
            chnum = i + 6;
        }
        if ((data >> i) & 0x01)
        {
            chip[chnum].eg_kon_c = 0x00;
            chip[chnum + 3].eg_kon_c = 0x00;
            OPL3_ChannelUpdateAlg(chip, chnum);
            OPL3_ChannelUpdateAlg(chip, chnum + 3);
        }
    }
}