unsigned __int8 __cdecl fsp_test_invert_cmd(unsigned __int8 reg_val)
{
    // 0xE9 (~0x16), 0xEE (~0x11), 0xF2 (~0x0D), 0xFF (~0x00)
    if (reg_val == 0xE9 || reg_val == 0xEE || reg_val == 0xF2 || reg_val == 0xFF)
        return ~reg_val;
    else
        return reg_val;
}