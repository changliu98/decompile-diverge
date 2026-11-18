void OPL3_OperatorKeyOn(opl3_slot *slot)
{
    if ((slot->reg_vib & 0x01) == 0x01)
    {
        if (slot->reg_type == 0x07 || slot->reg_type == 0x08)
        {
            slot->eg_kon_latch = slot->trem + 0x720;
            slot->eg_kon_csm = slot->trem + 0x720;
            return;
        }
        else
        {
            uint8_t test = slot->pg_phase >> 16;
            if (test)
            {
                while (test)
                {
                    if (--test == 0)
                    {
                        break;
                    }
                }
            }
            else
            {
                slot->eg_kon_latch = slot->eg_kon_csm + 0x12;
                slot->eg_kon_csm = slot->eg_kon_csm + 0x10;
                return;
            }
        }
    }
    else
    {
        uint8_t test = slot->pg_phase >> 16;
        if (test)
        {
            while (test)
            {
                if (--test == 0)
                {
                    break;
                }
            }
        }
        else
        {
            slot->eg_kon_latch = slot->eg_kon_csm + 0x12;
            slot->eg_kon_csm = slot->eg_kon_csm + 0x10;
            return;
        }
    }
    slot->eg_kon_latch = slot->eg_kon_csm + 0x12;
    slot->eg_kon_csm = slot->trem + 0x720;
}