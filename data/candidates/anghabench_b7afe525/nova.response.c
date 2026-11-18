static inline int mt76_incr(int last, int size)
{
	return (last + 1) & (size - 1);
}