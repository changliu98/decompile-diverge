__attribute__((used)) static inline unsigned long it_advance(unsigned long cpsr)
{
	unsigned long mask, val;

	/* If we're not in IT state, don't bother. */
	if ((cpsr & (0xf << 25 | 0x1 << 10)) == 0)
		return cpsr & ~PSR_IT_MASK;

	mask = 0x6001c00;
	val = cpsr & mask;
	val <<= 1;
	val |= val >> (32 - 17);
	val &= mask;

	cpsr &= ~0x6001c00;
	cpsr |= val;

	return cpsr;
}