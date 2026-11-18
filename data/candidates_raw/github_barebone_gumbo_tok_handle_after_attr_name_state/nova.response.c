static int func0(struct nand_chip *this, uint8_t *buf, loff_t offs,
			    size_t len)
{
	uint8_t *p = buf;
	uint8_t cmd;
	int i;

	i = (offs + 1) / 64;

	switch (i) {
	case 0:
		cmd = 0x2a;
		break;
	case 1:
		cmd = 0x24;
		break;
	case 2:
		cmd = 0x22;
		break;
	default:
		cmd = 0x00;
		break;
	}

	
	send_command(this, cmd);

	
	send_address(this, offs);

	
	send_count(this, len);

	
	send_read_count(this, len);

	
	while (len--) {
		writeb(0x02, this->legacy.IO_ADDR_W);
		writeb(0x22, this->legacy.IO_ADDR_W);
		writeb(0xff, this->legacy.IO_ADDR_W);

		writeb(0x02, this->legacy.IO_ADDR_W);
		writeb(0x10, this->legacy.IO_ADDR_W);

		writeb(0x02, this->legacy.IO_ADDR_W);
		writeb(0x22, this->legacy.IO_ADDR_W);

		*p++ = readb(this->legacy.IO_ADDR_R);
	}

	return p - buf;
}