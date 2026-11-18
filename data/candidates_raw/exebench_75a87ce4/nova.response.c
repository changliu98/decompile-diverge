void func0(struct dvb_frontend *fe, unsigned char *buf)
{
	buf[1] = fe->ops.tuner_ops.set_params;
}