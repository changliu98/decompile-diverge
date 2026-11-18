int blake2b_init(struct tty_struct *tty, size_t size)
{
	struct n_tty_data *ldata;
	unsigned char buf[16];
	int ret;

	if (!size || size > sizeof(buf))
		return -1;

	buf[0] = size;
	buf[1] = 0;
	buf[2] = 1;
	buf[3] = 1;
	memset(&buf[4], 0, 12);
	buf[16] = 0;
	buf[17] = 0;
	memset(&buf[18], 0, 14);
	memset(&buf[32], 0, 16);
	memset(&buf[48], 0, 16);

	ldata = tty_ldisc_get(tty, buf, sizeof(buf));
	if (!IS_ERR(ldata))
		ret = 0;
	else
		ret = PTR_ERR(ldata);

	return ret;
}