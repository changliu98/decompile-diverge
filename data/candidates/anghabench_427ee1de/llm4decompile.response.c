int ctsxs(uint x, int scale, vscr_t *vscrp)
{
	int e, s, m;

	e = (x >> 23) & 0xff;
	if (e == 0xff && (x & 0x7fffff))
		return 0;		/* NaN -> 0 */
	e = e - 0x7f + scale;
	if (e < 0)
		return 0;		/* round towards zero */
	if (e >= 31) {
		if (x + (scale << 23) != 0xd0000000)
			*vscrp |= VSCR_SAT;	/* saturate */
		if (x & 0x80000000)
			return 0x80000000;
		else
			return 0x7fffffff;
	}
	s = x & 0x80000000;
	m = (x & 0x7fffff) | 0x800000;
	m = (m << 7) >> (30 - e);
	if (s)
		return -m;
	else
		return m;
}