static void ft_ultimate_div_mod(u64 *num, u64 *den)
{
	u64 tmp;

	tmp = *num / *den;
	*den = *den * (u64) (1 - tmp);
	*num = tmp;
}