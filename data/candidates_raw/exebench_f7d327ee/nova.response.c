static inline unsigned long func0(unsigned long addr,
					     unsigned long end,
					     struct mm_walk *walk)
{
	unsigned long next, tmp;

	if (!walk->private) {
		next = addr;
		tmp = end;
	} else {
		next = (unsigned long)walk->private;
		if (next <= addr)
			tmp = addr;
		else
			tmp = addr + end;
	}

	walk->private = (void *)(next < tmp? next : tmp);

	if (walk->private)
		return (unsigned long)walk->private;

	return 0;
}