static int foo(struct dvb_frontend *fe)
{
	fe->tuner_priv = NULL;
	return 0;
}