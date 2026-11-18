unsigned char get_parameter_rate(OPLL_SLOT *slot)
{
    if((slot->type&0x01) || slot->key_flag)
    {
        switch(slot->eg_state)
        {
            case 0x00:
                return slot->patch->AR;
            case 0x01:
                return slot->patch->DR;
            case 0x02:
                return slot->patch->EG ? 0 : slot->patch->RR;
            case 0x03:
                return slot->sus_flag ? 5 : (slot->patch->EG ? slot->patch->RR : 7);
            case 0x04:
                return 12;
            default:
                return 0;
        }
    }
    return 0;
}