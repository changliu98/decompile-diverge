void OPL2_ChannelSetupCon(opl2_channel *channel)
{
    if (channel->chtype == 1)
    {
        if (channel->ch_num == 7 || channel->ch_num == 8)
        {
            channel->slotz[0]->mod = &channel->chip->zeromod;
            channel->slotz[1]->mod = &channel->chip->zeromod;
        }
        else
        {
            if (channel->con == 0)
            {
                channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
                channel->slotz[1]->mod = &channel->slotz[0]->out;
            }
            else if (channel->con == 1)
            {
                channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
                channel->slotz[1]->mod = &channel->chip->zeromod;
            }
        }
    }
    else
    {
        if (channel->con == 0)
        {
            channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
            channel->slotz[1]->mod = &channel->slotz[0]->out;
        }
        else if (channel->con == 1)
        {
            channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
            channel->slotz[1]->mod = &channel->chip->zeromod;
        }
    }
}