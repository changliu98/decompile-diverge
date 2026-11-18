static void func0(u64 *reg, u32 value)
{
	u32 field, pos;

	pos = value / 32;
	field = value % 32;
	reg[pos] |= (1 << field);
}