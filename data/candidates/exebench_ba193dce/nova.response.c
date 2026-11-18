static int nogr_prompt_dir(struct dvb_frontend *fe,
				   u16 *signal_strength, u16 *signal_to_noise)
{
	*signal_strength = 1;
	*signal_to_noise = 0;
	return 0;
}