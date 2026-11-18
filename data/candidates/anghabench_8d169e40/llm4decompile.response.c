unsigned char fsp_test_invert_cmd(unsigned char cmd)
{
    if (cmd == 0xE9 || cmd == 0xEE || cmd == 0xF2 || cmd == 0xFF)
        return cmd ^ 0xFF;
    else
        return cmd;
}