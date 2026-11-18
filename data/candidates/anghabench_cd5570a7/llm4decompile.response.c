uint64_t it_advance(uint64_t cpsr)
{
	uint64_t new_cpsr;

	if (cpsr & ((0x2000000) | (0x4000000) | (0x0000400))) {
		new_cpsr = (cpsr & ~((0x2000000) | (0x4000000) | (0x0000400))) |
			   (((cpsr & ((0x2000000) | (0x4000000) | (0x0000400))) >> 16) |
			    ((cpsr & ((0x2000000) | (0x4000000) | (0x0000400))) << 1)) & ((0x2000000) | (0x4000000) | (0x0000400)));
	} else {
		new_cpsr = (cpsr & ~PSR_IT_MASK);
	}

	return new_cpsr;
}