__attribute__((used)) static inline int mt76_incr(int idx, int inc)
{
	return (idx + 1) & (inc - 1);
}