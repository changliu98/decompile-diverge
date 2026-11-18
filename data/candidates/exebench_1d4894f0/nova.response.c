static void stack4_replace_top(struct pt_regs *regs, unsigned long mask)
{
	regs->psw.mask &= ~mask;
	regs->psw.mask |= mask;
}