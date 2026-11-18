static inline u32 func0(u32 *ptr, u32 val)
{
	u32 reg;

	reg = *ptr;
	reg = val;
	*ptr = reg;

	return reg;
}