static void func0(void *data, unsigned long mask)
{
	struct func0_struct *wakeup = data;
	unsigned long *bits = &wakeup->bits;
	unsigned long old, new;

	do {
		old = *bits;
		new = old & mask;
	} while (cmpxchg(bits, old, new)!= old);
}