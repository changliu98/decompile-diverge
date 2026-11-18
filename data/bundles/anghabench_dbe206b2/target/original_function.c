int get_opcode(unsigned char *addr, unsigned int *opcode)
{
	int len;

	if (*addr == 0x0F) {
		/* 0x0F is extension instruction */
		*opcode = *(unsigned short *)addr;
		len = 2;
	} else {
		*opcode = *addr;
		len = 1;
	}

	return len;
}