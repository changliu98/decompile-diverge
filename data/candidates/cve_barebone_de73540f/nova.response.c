static int lldp_private_8023_print(struct pt_regs *regs, unsigned char *instr,
			    unsigned int length)
{
	unsigned short *pc = (unsigned short *)regs->pc;
	unsigned short *addr;
	unsigned short instr16;
	unsigned int i;

	
	switch (length) {
	case 4:
		instr16 = *(unsigned short *)(instr + 2);
		addr = (unsigned short *)(regs->pc + 2);
		printk("%s%08lx%04x%s",
		       instr16 & 0x0f00? "?" : "jmp",
		       regs->pc + 2, instr16,
		       instr16 & 0x0f00? "?" : "");
		break;
	case 9:
		instr16 = *(unsigned short *)(instr + 4);
		addr = (unsigned short *)(regs->pc + 4);
		printk("%s%08lx%04x%s",
		       instr16 & 0x0f00? "?" : "jmp",
		       regs->pc + 4, instr16,
		       instr16 & 0x0f00? "?" : "");
		break;
	default:
		i = 0;
		break;
	}

	
	while (1) {
		instr16 = *addr;
		printk("%s%08lx%04x%s",
		       instr16 & 0x0f00? "?" : "jmp",
		       (unsigned long)addr, instr16,
		       instr16 & 0x0f00? "?" : "");
		addr++;
		i++;
		if (i > 10)
			break;
	}

	return i;
}