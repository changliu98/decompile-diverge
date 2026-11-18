__attribute__((used)) static inline u32 TOY_A_INT(u32 val)
{
	return ((val & 0xfffff000) << 4) | (val & 0xfff);
}