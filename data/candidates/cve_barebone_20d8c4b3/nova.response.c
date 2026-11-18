static int svc_parse_slice(struct us_data *us,
			    unsigned char *status,
			    struct ene_ub6250_info *info)
{
	int retval = -1;
	unsigned char *buf;

	usb_stor_dbg(us, "Reading status...\n");

	
	do {
		info->buf_size = usb_stor_bulk_transfer_buf(us, 0x82,
							   info->rbuf,
							   -1, NULL);
		buf = info->rbuf;
		if (info->buf_size < 10)
			retval = -1;
		else
			retval = usb_stor_bulk_transfer_buf(us, 0x83,
							   info->rbuf,
							   -1, NULL);
		if (retval < 0)
			break;

		info->rbuf_status = buf[0];
		info->rbuf_status_2 = buf[1];
		if (!info->rbuf_status)
			retval = -2;
		if (!info->rbuf_status_2)
			retval = -3;

		info->buf_data = (unsigned int)buf[2] + ((unsigned int)buf[3] << 8);
		if (!info->buf_data)
			retval = -4;

		info->buf_data_2 = (unsigned int)buf[4] + ((unsigned int)buf[5] << 8);
		if (!info->buf_data_2)
			retval = -5;

		info->buf_data_3 = (unsigned int)buf[6] + ((unsigned int)buf[7] << 8);
		if (!info->buf_data_3)
			retval = -6;

		info->buf_data_4 = (unsigned int)buf[8] + ((unsigned int)buf[9] << 8);
		if (!info->buf_data_4)
			retval