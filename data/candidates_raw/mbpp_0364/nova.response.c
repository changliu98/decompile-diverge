static int func0(struct dib8000_state *state)
{
	u16 agc, boot;

	agc = dib8000_read_word(state, 48);
	boot = dib8000_read_word(state, 49);

	if (agc > boot)
		return dib8000_read_word(state, 48);
	else
		return dib8000_read_word(state, 49);
}