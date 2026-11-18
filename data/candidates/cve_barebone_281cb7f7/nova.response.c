static int dhcpv6_print(struct us_data *us,
			    void* buffer,
			    unsigned int buffer_length,
			    int use_sg)
{
	unsigned short *data = (unsigned short *)buffer;
	unsigned short *sg_data;
	unsigned int i, j, k;
	int result;

	for (i = 0; i < buffer_length; i += 4) {
		unsigned short lba = (data[i] << 8) | data[i + 1];
		unsigned short sector_count = (data[i + 2] << 8) | data[i + 3];

		usb_stor_dbg(us, "lba: %d, sector_count: %d\n",
			     lba, sector_count);

		for (j = 0; j < sector_count; j++) {
			unsigned char *buf = (unsigned char *)&data[i + 4];
			unsigned char *sg_buf;

			sg_data = (unsigned short *)(buf + j * 2048);

			usb_stor_dbg(us, "lba: %d, sector: %d\n",
				     lba, j);

			sg_buf = usb_stor_sg_buf_next(us, &sg_data, use_sg);

			for (k = 0; k < 2048; k++) {
				if (sg_buf == NULL) {
					result = -1;
					goto out;
				}
				*sg_buf++ = buf[k];
			}
		}
	}

	result = 0;
out:
	return result;
}