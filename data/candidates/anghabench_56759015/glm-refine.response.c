unsigned int __cdecl dac_convert_reg(unsigned int channel)
{
    unsigned int is_odd_channel = channel & 1;
    return 112 + (2 * is_odd_channel);
}