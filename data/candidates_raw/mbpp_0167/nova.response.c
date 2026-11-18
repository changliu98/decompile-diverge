static inline int func0(int x)
{
	int log = 0;

	if (x &&!(x & (x - 1)))
		return x;

	while (x) {
		x >>= 1;
		log++;
	}

	return 1 << log;
}