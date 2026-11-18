int dac_convert_reg(int reg)
{
	int channel;

	channel = reg & 0x01;
	return 0x70 + (channel << 1);
}