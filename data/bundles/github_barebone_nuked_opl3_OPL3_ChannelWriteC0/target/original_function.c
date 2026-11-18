static void OPL3_ChannelWriteC0(opl3_channel *channel, uint8_t data)
{
    channel->fb = (data & 0x0e) >> 1;
    channel->con = data & 0x01;
    OPL3_ChannelUpdateAlg(channel);
    if (channel->chip->newm)
    {
        channel->cha = ((data >> 4) & 0x01) ? ~0 : 0;
        channel->chb = ((data >> 5) & 0x01) ? ~0 : 0;
        channel->chc = ((data >> 6) & 0x01) ? ~0 : 0;
        channel->chd = ((data >> 7) & 0x01) ? ~0 : 0;
    }
    else
    {
        channel->cha = channel->chb = (uint16_t)~0;
        // TODO: Verify on real chip if DAC2 output is disabled in compat mode
        channel->chc = channel->chd = 0;
    }
#if OPL_ENABLE_STEREOEXT
    if (!channel->chip->stereoext)
    {
        channel->leftpan = channel->cha << 16;
        channel->rightpan = channel->chb << 16;
    }
#endif
}