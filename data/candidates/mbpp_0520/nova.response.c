static u32 func0(struct dvb_frontend *fe, u8 num)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 frequency = c->frequency;
	u8 pwr = c->strength.stat[0].uvalue;
	u8 i;

	pwr = simple_moving_avg(pwr, frequency);
	for (i = 2; i < num; i++)
		pwr = simple_moving_avg(pwr, c->strength.stat[i].uvalue);

	return pwr;
}