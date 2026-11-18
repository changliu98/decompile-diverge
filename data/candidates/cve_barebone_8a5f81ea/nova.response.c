static int pktap_if_print(struct nand_chip *chip, const u8 *buf,
				   u8 *code)
{
	unsigned int len, offs = 0;
	u32 data, data_offs;
	u8 *p;

	
	len = buf[3];
	do {
		if (len > 108) {
			chip->legacy.cmdfunc(chip, NAND_CMD_ERASE1,
					     -1, -1);
			offs = 0;
		}
		data = ((u32)buf[offs + 11] << 24) |
			((u32)buf[offs + 10] << 16) |
			((u32)buf[offs + 9] << 8) |
			buf[offs + 8];
		if (data > 108) {
			chip->legacy.cmdfunc(chip, NAND_CMD_ERASE2,
					     -1, -1);
			offs = 0;
		}
		data_offs = data;
		p = (u8 *)code;
		while (data_offs) {
			if (!chip->legacy.write_byte)
				chip->legacy.write_buf(chip, code, len);
			else
				data_offs -= chip->legacy.write_byte(chip,
								     code, len);
			code += data_offs;
			data_offs = data;
		}
		len = buf[offs + 3];
		offs += 12;
	} while (len);

	return offs;
}