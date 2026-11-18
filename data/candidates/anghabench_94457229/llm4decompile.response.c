u8 clk_div_even_up(u8 div)
{
	if (div == 1)
		return 1;
	else
		return ((div + 1) & ~1);
}