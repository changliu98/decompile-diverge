static void bitmap_free(void *dst, u32 v)
{
	u32 mask = (1 << ((v % 32) + 1)) - 1;
	u32 *q = dst;
	q[v / 32] &= mask;
}