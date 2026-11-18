static void func0(void *info, u64 *info_2)
{
	u64 *p = info;
	u64 *q = info;
	u64 *r = info;
	u64 *x = info_2;

	asm volatile("cpuid"
		     : "=a" (*p),
		       "=b" (*q),
		       "=c" (*r),
		       "=d" (*x)
		     : "0" (*p), "c" (*q));
}