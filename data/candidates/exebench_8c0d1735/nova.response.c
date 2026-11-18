static inline u8 and_peep2_qi(u8 reg, u8 *pval)
{
	*pval = reg & 0x5f;
	return reg;
}