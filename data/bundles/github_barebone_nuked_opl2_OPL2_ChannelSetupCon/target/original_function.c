static void OPL2_ChannelSetupCon(opl2_channel *channel)
{
    if (channel->chtype == ch_drum)
    {
        if (channel->ch_num == 7 || channel->ch_num == 8)
        {
            channel->slotz[0]->mod = &channel->chip->zeromod;
            channel->slotz[1]->mod = &channel->chip->zeromod;
            return;
        }
        switch (channel->con)
        {
        case 0x00:
            channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
            channel->slotz[1]->mod = &channel->slotz[0]->out;
            break;
        case 0x01:
            channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
            channel->slotz[1]->mod = &channel->chip->zeromod;
            break;
        }
        return;
    }
    switch (channel->con)
    {
    case 0x00:
        channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
        channel->slotz[1]->mod = &channel->slotz[0]->out;
        break;
    case 0x01:
        channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
        channel->slotz[1]->mod = &channel->chip->zeromod;
        break;
    }
}