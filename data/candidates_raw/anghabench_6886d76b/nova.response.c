static inline int func0(unsigned long v)
{
	int l = 0;
	while (v >>= 1)
		l++;
	return l;
}