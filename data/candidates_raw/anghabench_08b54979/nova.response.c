static inline u32 func0(u32 val, u32 mask, u32 writeval)
{
	return (val & ~mask) | (~writeval & mask);
}