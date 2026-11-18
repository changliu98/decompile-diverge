static int func0(struct dvb_frontend *fe, u8 id, u8 *buf)
{
	if (fe)
		id = 1;
	buf[0] = id;

	return 0;
}