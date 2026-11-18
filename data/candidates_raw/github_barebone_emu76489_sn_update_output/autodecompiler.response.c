void OPN2_PhaseGenerate(ym3438_t *chip)
{
    Bit32u slot;
    Bit32u test_dac;
    Bit32u bit_14_15;

    chip->pg_phase += chip->pg_inc;
    bit_14_15 = chip->pg_phase >> 24;
    chip->pg_phase &= 0xffffff;

    chip->pg_test_dac += chip->pg_test_dac_inc;
    if ((chip->pg_test_dac + 0x100) & 0x200)
    {
        if (chip->mode_test_2c)
        {
            test_dac = chip->test_dac & 0x1ff;
            chip->test_dac = (test_dac >> 1) | (parity(test_dac & 0x09) << 15);
        }
        else
        {
            test_dac = chip->test_dac;
            chip->test_dac = (test_dac >> 1) | ((test_dac & 0x01) << 15);
        }
        if (chip->write_msl1)
        {
            chip->pg_test_dac = chip->pg_test_dac - chip->op_out[12];
        }
        else
        {
            chip->pg_test_dac = chip->pg_test_dac - chip->op_out[14];
        }
    }

    if (chip->test_dac & 0x01)
    {
        chip->pg_fnum_h += (voltbl[chip->pg_fnum_h] << 4) + (Bit32s)chip->pg_fnum_h_table;
    }
    chip->pg_fnum_h >>= 1;

    for (slot = 0; slot < 4; slot++)
    {
        chip->pg_slot_phase[slot] += chip->pg_slot_incr[slot];
        if (chip->pg_slot_phase[slot] & 0x400)
        {
            if (chip->pg_slot_kon_csm[slot] >= 2)
            {
                chip->pg_slot_kon_csm[slot] = (chip->pg_slot_kon_csm[slot] == 0x0f) ? 0 : 1;
                chip->pg_slot_phase[slot] -= chip->pg_slot_kon_csm[slot];
            }
            else
            {
                chip->pg_slot_kon_csm[slot] = 1;
            }
        }
        else
        {
            if (chip->pg_slot_kon_csm[slot] && !chip->pg_slot_kon_csm_1)
            {
                chip->pg_slot_out[slot] += (voltbl[chip->pg_slot_fb[slot]] << 4) + (Bit32s)chip->pg_slot_out[slot];
            }
            chip->pg_slot_out[slot] >>= 1;
        }
    }
}