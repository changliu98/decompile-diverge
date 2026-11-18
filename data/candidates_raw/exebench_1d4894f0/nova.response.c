static void func0(struct pt_regs *regs, unsigned long mask)
{
	regs->psw.mask &= ~mask;
	regs->psw.mask |= mask;
}