unsigned int __cdecl dac_lsb_4020_reg(unsigned int channel)
{
    unsigned int is_odd_channel = channel & 1;
    return (is_odd_channel * 4) + 112;
}