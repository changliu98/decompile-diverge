static char BS_ReadByte(struct vc_data *vc)
{
	unsigned char c;
	char ret;

	if (!vc->vc_x || vc->vc_y >= vc->vc_rows) {
		while (1) {
			if (vc->vc_decom)
				puts_queue(vc->vc_decom);
			if (!vc->vc_decom || vc->vc_y >= vc->vc_rows)
				break;
			vc->vc_x = 0;
		}
		vc->vc_y = vc->vc_rows;
		return 0;
	}

	do {
		if (vc->vc_decom)
			puts_queue(vc->vc_decom);
		if (!vc->vc_decom || vc->vc_y >= vc->vc_rows)
			break;
		vc->vc_x = 0;
	} while (0);

	do {
		ret = get_char(vc);
		if (ret == 0x04)
			vc->vc_y++;
		else
			vc->vc_y = 0;
	} while (ret == 0x04);

	return ret;
}