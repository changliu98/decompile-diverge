void __cdecl OPL3_ChannelSetupAlg(opl3_channel *channel)
{
    opl3_chip *chip = channel->chip;
    opl3_channel *pair = channel->pair;
    opl3_slot **slots = channel->slotz;
    opl3_slot **pair_slots = pair ? pair->slotz : NULL;
    int16_t **chan_out = channel->out;
    int16_t **pair_out = pair ? pair->out : NULL;
    int16_t *zeromod = &chip->zeromod;

    if (channel->chtype == 3)
    {
        if (channel->ch_num == 7 || channel->ch_num == 8)
        {
            slots[0]->mod = zeromod;
            slots[1]->mod = zeromod;
        }
        else if (channel->alg & 1)
        {
            slots[0]->mod = &slots[0]->fbmod;
            slots[1]->mod = zeromod;
        }
        else
        {
            slots[0]->mod = &slots[0]->fbmod;
            slots[1]->mod = &slots[0]->out;
        }
    }
    else if (!(channel->alg & 8))
    {
        if (channel->alg & 4)
        {
            // 4-op channel setup
            pair_out[0] = zeromod;
            pair_out[1] = zeromod;
            pair_out[2] = zeromod;
            pair_out[3] = zeromod;

            switch (channel->alg & 3)
            {
                case 0:
                    pair_slots[0]->mod = &pair_slots[0]->fbmod;
                    pair_slots[1]->mod = &pair_slots[0]->out;
                    slots[0]->mod = &pair_slots[1]->out;
                    slots[1]->mod = &slots[0]->out;
                    chan_out[0] = &slots[1]->out;
                    chan_out[1] = zeromod;
                    chan_out[2] = zeromod;
                    chan_out[3] = zeromod;
                    break;

                case 1:
                    pair_slots[0]->mod = &pair_slots[0]->fbmod;
                    pair_slots[1]->mod = &pair_slots[0]->out;
                    slots[0]->mod = zeromod;
                    slots[1]->mod = &slots[0]->out;
                    chan_out[0] = &pair_slots[1]->out;
                    chan_out[1] = &slots[1]->out;
                    chan_out[2] = zeromod;
                    chan_out[3] = zeromod;
                    break;

                case 2:
                    pair_slots[0]->mod = &pair_slots[0]->fbmod;
                    pair_slots[1]->mod = zeromod;
                    slots[0]->mod = &pair_slots[1]->out;
                    slots[1]->mod = &slots[0]->out;
                    chan_out[0] = &pair_slots[0]->out;
                    chan_out[1] = &slots[1]->out;
                    chan_out[2] = zeromod;
                    chan_out[3] = zeromod;
                    break;

                case 3:
                    pair_slots[0]->mod = &pair_slots[0]->fbmod;
                    pair_slots[1]->mod = zeromod;
                    slots[0]->mod = &pair_slots[1]->out;
                    slots[1]->mod = zeromod;
                    chan_out[0] = &pair_slots[0]->out;
                    chan_out[1] = &slots[0]->out;
                    chan_out[2] = &slots[1]->out;
                    chan_out[3] = zeromod;
                    break;
            }
        }
        else if (channel->alg & 1)
        {
            // 2-op channel setup (Algorithm 1)
            slots[0]->mod = &slots[0]->fbmod;
            slots[1]->mod = zeromod;
            chan_out[0] = &slots[0]->out;
            chan_out[1] = &slots[1]->out;
            chan_out[2] = zeromod;
            chan_out[3] = zeromod;
        }
        else
        {
            // 2-op channel setup (Algorithm 0)
            slots[0]->mod = &slots[0]->fbmod;
            slots[1]->mod = &slots[0]->out;
            chan_out[0] = &slots[1]->out;
            chan_out[1] = zeromod;
            chan_out[2] = zeromod;
            chan_out[3] = zeromod;
        }
    }
}