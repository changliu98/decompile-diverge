static inline u32 clk_div_even_up(u32 val)
{
	u32 ret;

	if (val == 1)
		ret = 1;
	else
		ret = val + 1;

	return ret & 0x3f;
}