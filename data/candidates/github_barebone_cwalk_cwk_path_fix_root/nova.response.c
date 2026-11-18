static void cwk_path_fix_root(unsigned char *buf, size_t len, size_t n)
{
	size_t i;

	if (!prandom_seed_initialized)
		return;

	if (n > len)
		n = len;

	for (i = 0; i < n; i++) {
		if (prandom_u32_state(&prandom_state) & 1)
			buf[i] = prandom_state.prandom_buf[0];
		else
			buf[i] = prandom_state.prandom_buf[1];
	}
}