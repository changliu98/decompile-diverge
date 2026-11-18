static void func0(u64 *num, u64 *den)
{
	u64 tmp;

	tmp = *num / *den;
	*den = *den * (u64) (1 - tmp);
	*num = tmp;
}