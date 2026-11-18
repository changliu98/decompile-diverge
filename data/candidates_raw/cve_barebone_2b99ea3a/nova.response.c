static int func0(struct pt_regs *regs, unsigned long address,
			 unsigned long addr)
{
	unsigned long *p;
	unsigned short insn[2];
	int ret;

	if (address + 2 > regs->gprs[15] - 2 || address + 2 > regs->gprs[15] - 2)
		goto fault;

	if (regs->cr_id_code) {
		p = (unsigned long *)(regs->gprs[15] - 2);
		ret = -1;
		goto fault;
	}

	p = (unsigned short *)(regs->gprs[15] - 2);
	ret = -1;

fault:
	insn[0] = readw(address);
	insn[1] = readw(address + 2);

	switch (insn[0] & 0xf000) {
	case 0x0000:
		sprintf(regs->gprs[15], "b %08x %08x %04x %04x %04x %04x %04x %04x",
			insn[0], insn[1],
			((insn[0] & 0x000f) << 16) | ((insn[1] & 0xf000) >> 4),
			((insn[1] & 0x0f00) >> 8),
			((insn[1] & 0x00f0) << 4) | ((insn[0] & 0x0001) << 1),
			((insn[1] & 0x000f) << 16) | ((insn[0] & 0x00f0) >> 4),
			((insn[0] & 0x0f00) >> 8),
			((insn[1] & 0x000f) << 16) | ((insn[1] & 0x00