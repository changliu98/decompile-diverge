int chdlc_if_print(struct us_data *us, unsigned char *data,
		      unsigned int len)
{
	int rc;
	unsigned int pipe = data[5];
	unsigned int data_len = data[4];

	if (data_len < 5) {
		usb_stor_dbg(us, "load_sg_from_buf data buffer too short\n");
		rc = data_len;
	} else
		rc = usb_stor_bulk_transfer_sg(us, pipe, (struct scatterlist *)
				(data + 8), data_len, &len);

	return rc;
}