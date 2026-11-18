int dac_lsb_4020_reg(int channel)
{
	return 0x70 + 4 * (channel % 2);
}