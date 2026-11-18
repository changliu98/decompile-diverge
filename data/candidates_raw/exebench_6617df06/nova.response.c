static inline int func0(int irq, void *data)
{
	unsigned int *mask = data;
	int ret;

	ret = *mask ^ (1 << irq);
	*mask = ret;

	return ret;
}