static void OPL3_ChannelSetupAlg(opl3_channel *channel)
{
    if (channel->chtype == ch_drum)
    {
        if (channel->ch_num == 7 || channel->ch_num == 8)
        {
            channel->slotz[0]->mod = &channel->chip->zeromod;
            channel->slotz[1]->mod = &channel->chip->zeromod;
            return;
        }
        switch (channel->alg & 0x01)
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
    if (channel->alg & 0x08)
    {
        return;
    }
    if (channel->alg & 0x04)
    {
        channel->pair->out[0] = &channel->chip->zeromod;
        channel->pair->out[1] = &channel->chip->zeromod;
        channel->pair->out[2] = &channel->chip->zeromod;
        channel->pair->out[3] = &channel->chip->zeromod;
        switch (channel->alg & 0x03)
        {
        case 0x00:
            channel->pair->slotz[0]->mod = &channel->pair->slotz[0]->fbmod;
            channel->pair->slotz[1]->mod = &channel->pair->slotz[0]->out;
            channel->slotz[0]->mod = &channel->pair->slotz[1]->out;
            channel->slotz[1]->mod = &channel->slotz[0]->out;
            channel->out[0] = &channel->slotz[1]->out;
            channel->out[1] = &channel->chip->zeromod;
            channel->out[2] = &channel->chip->zeromod;
            channel->out[3] = &channel->chip->zeromod;
            break;
        case 0x01:
            channel->pair->slotz[0]->mod = &channel->pair->slotz[0]->fbmod;
            channel->pair->slotz[1]->mod = &channel->pair->slotz[0]->out;
            channel->slotz[0]->mod = &channel->chip->zeromod;
            channel->slotz[1]->mod = &channel->slotz[0]->out;
            channel->out[0] = &channel->pair->slotz[1]->out;
            channel->out[1] = &channel->slotz[1]->out;
            channel->out[2] = &channel->chip->zeromod;
            channel->out[3] = &channel->chip->zeromod;
            break;
        case 0x02:
            channel->pair->slotz[0]->mod = &channel->pair->slotz[0]->fbmod;
            channel->pair->slotz[1]->mod = &channel->chip->zeromod;
            channel->slotz[0]->mod = &channel->pair->slotz[1]->out;
            channel->slotz[1]->mod = &channel->slotz[0]->out;
            channel->out[0] = &channel->pair->slotz[0]->out;
            channel->out[1] = &channel->slotz[1]->out;
            channel->out[2] = &channel->chip->zeromod;
            channel->out[3] = &channel->chip->zeromod;
            break;
        case 0x03:
            channel->pair->slotz[0]->mod = &channel->pair->slotz[0]->fbmod;
            channel->pair->slotz[1]->mod = &channel->chip->zeromod;
            channel->slotz[0]->mod = &channel->pair->slotz[1]->out;
            channel->slotz[1]->mod = &channel->chip->zeromod;
            channel->out[0] = &channel->pair->slotz[0]->out;
            channel->out[1] = &channel->slotz[0]->out;
            channel->out[2] = &channel->slotz[1]->out;
            channel->out[3] = &channel->chip->zeromod;
            break;
        }
    }
    else
    {
        switch (channel->alg & 0x01)
        {
        case 0x00:
            channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
            channel->slotz[1]->mod = &channel->slotz[0]->out;
            channel->out[0] = &channel->slotz[1]->out;
            channel->out[1] = &channel->chip->zeromod;
            channel->out[2] = &channel->chip->zeromod;
            channel->out[3] = &channel->chip->zeromod;
            break;
        case 0x01:
            channel->slotz[0]->mod = &channel->slotz[0]->fbmod;
            channel->slotz[1]->mod = &channel->chip->zeromod;
            channel->out[0] = &channel->slotz[0]->out;
            channel->out[1] = &channel->slotz[1]->out;
            channel->out[2] = &channel->chip->zeromod;
            channel->out[3] = &channel->chip->zeromod;
            break;
        }
    }
}