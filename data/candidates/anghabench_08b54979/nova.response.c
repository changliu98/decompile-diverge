static inline u32 F(u32 val, u32 mask, u32 writeval)
{
	return (val & ~mask) | (~writeval & mask);
}