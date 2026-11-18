__attribute__((used)) static inline int dac_convert_reg(int channel)
{
	return 0x70 + (2 * (channel & 1));
}