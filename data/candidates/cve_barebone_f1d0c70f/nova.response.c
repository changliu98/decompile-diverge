static void ip_optprint(struct sd *sd, u8 *data, unsigned len)
{
	const struct ov_regs *regs = &ov_regs[0];
	unsigned char *p = data;
	unsigned char *end = data + len;

	while (p < end) {
		unsigned reg;
		unsigned value;

		reg = *p++;
		if (reg == 0)
			break;

		if (p >= end - 1)
			break;

		value = *p++;

		if (reg == 1) {
			if (value == 0)
				break;
			if (value == 1)
				continue;
			if (value == 2)
				regs = &ov_regs[1];
			if (value == 3)
				regs = &ov_regs[2];
			if (value == 4)
				regs = &ov_regs[3];
			continue;
		}

		if (value == 0)
			continue;
		if (value == 1)
			break;

		if (p >= end - 2)
			break;

		value = *p++ << 8 | *p++;

		if (value == 0x0000)
			continue;
		if (value == 0xffff)
			break;

		reg_w(sd, regs, reg, value);
	}
	reg_w(sd, &ov_regs[0], 0x00, 0x0000);
}