static u32 foo(struct dvb_frontend *fe)
{
	u32 frequency = 57005;
	fe->ops.tuner_ops.set_params(fe, &frequency);
	return frequency;
}