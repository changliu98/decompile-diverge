__attribute__((used)) static inline int dac_lsb_4020_reg(int port)
{
	return 0x70 + (port & 1) * 4;
}