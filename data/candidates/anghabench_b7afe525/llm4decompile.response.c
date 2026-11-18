u16 mt76_incr(u16 idx, u16 size)
{
	return (idx + 1) & (size - 1);
}