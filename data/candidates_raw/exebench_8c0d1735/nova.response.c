static inline u8 func0(u8 reg, u8 *pval)
{
	*pval = reg & 0x5f;
	return reg;
}