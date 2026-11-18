static void func0(u32 msr, u32 *low, u32 *high)
{
	u64 val;
	u32 mask_low = 0, mask_high = 0;

	
	asm volatile("func0 %0,%1,%2"
		: "=r" (val), "=r" (mask_low), "=r" (mask_high)
		: "0" (msr), "2" (low), "3" (high));

	*low = (u32) val;
	*high = (u32) (val >> 32);
}