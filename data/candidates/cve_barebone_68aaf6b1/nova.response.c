static int cbs_av1_read_uvlc(struct pt_regs *regs, unsigned long addr,
			unsigned long instr, struct pt_regs *fp_regs,
			unsigned int fp_regnum, unsigned long fp_val)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;
	unsigned int regnum;
	unsigned char buf[32];

	if (regs->int_code)
		regnum = get_regnum(addr);
	else
		regnum = 0;

	i = 0;
	j = 0;
	while (1) {
		if (i >= ARRAY_SIZE(fp_regs->gpr)) {
			snprintf(buf, sizeof(buf), "FPR%d", i);
			i = -1;
		}
		if (i < 32) {
			buf[i++] = (j >= jmp_regnum(addr))? '1' : '0';
			j++;
		} else {
			regnum = (regnum + (1 << (jmp_regnum(addr) - jmp_regnum(addr)) - 1)) & (jmp_regnum(addr) - 1);
			j = 0;
		}
		if (regnum >= fp_regnum)
			break;
	}
	if (regs->int_code)
		buf[i] = '\0';
	fp_val = fp_regs->fpr[regnum];

	printk_address(regs, regnum, instr, fp_val, buf);

	return fp_val;
}