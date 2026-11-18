static inline int test_and_change_bit(int irq, void *data)
{
	unsigned int *mask = data;
	int ret;

	ret = *mask ^ (1 << irq);
	*mask = ret;

	return ret;
}