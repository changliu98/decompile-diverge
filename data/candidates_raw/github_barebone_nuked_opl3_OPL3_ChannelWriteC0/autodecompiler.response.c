void OPL3_ChannelKeyOff(opl3_slot *slot, Bit8u type)
{
    slot->key = (type & 0x0e) >> 1;
    slot->trem = type & 0x01;
    OPL3_ChannelUpdateAlg(slot);
    if (slot->chip->newm)
    {
        slot->sintab = (type & 0x10) ? ~0 : 0;
        slot->eg_ssg_inv = (type & 0x20) ? ~0 : 0;
        slot->eg_ssg_nor = (type & 0x40) ? ~0 : 0;
        slot->eg_ssg_pmd = (type & 0x80) ? ~0 : 0;
        return;
    }
    slot->eg_ssg_inv = ~0;
    slot->sintab = ~0;
    slot->eg_ssg_nor = 0;
    slot->eg_ssg_pmd = 0;
    if (slot->eg_mode == OPL3_EG_SHUT_OFF && !slot->eg_ssg_inv)
    {
        slot->eg_mode = OPL3_EG_SHUT_OFF;
        slot->eg_state = OPL3_EG_OFF;
        slot->eg_timer = 0x00;
    }
}