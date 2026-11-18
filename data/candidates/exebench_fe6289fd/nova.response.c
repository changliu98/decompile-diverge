static unsigned long xchg8(unsigned long *ptr, unsigned long val)
{
	unsigned long ret = val;

	*ptr = ret;
	return ret;
}