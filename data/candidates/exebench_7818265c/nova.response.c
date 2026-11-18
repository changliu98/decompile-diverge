static inline u32 xchg(u32 *ptr, u32 val)
{
	u32 reg;

	reg = *ptr;
	reg = val;
	*ptr = reg;

	return reg;
}