void OPL3_ChannelWriteC0(struct OPL3_Channel *channel, uint8_t val) {
    channel->fcha = (val & 0xe) >> 1;
    channel->chd = val & 0x1;

    OPL3_ChannelUpdateAlg(channel);

    struct OPL3 *opl3 = (struct OPL3 *)channel->opl3;
    if (opl3->full_pan) {
        channel->cha = (val & 0x10) ? -1 : 0;
        channel->chb = (val & 0x20) ? -1 : 0;
        channel->chc = (val & 0x40) ? -1 : 0;
        channel->chd_int = (val & 0x80) ? -1 : 0;
    } else {
        channel->chb = -1;
        channel->cha = -1;
        channel->chd_int = 0;
        channel->chc = 0;
    }
}