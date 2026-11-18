static void func0(void *info, u64 val)
{
	u32 *reg = info;
	u32 lo, hi;

	__asm__ __volatile__("func0 %1,%2\n\t"
			     "adc %1,%2\n\t"
			     "adc %1,%2\n\t"
			     "adc %1,%2\n\t"
			     "adc %1,%2\n\t"
			     "adc %1,%2\n\t"
			     "adc %1,%2\n\t"
			     : "=r" (lo), "=r" (hi)
			     : "r" (val), "0" (0));

	*reg = lo;
	*(reg + 1) = hi;
}