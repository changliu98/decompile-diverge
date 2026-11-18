char *
bittok2str_internal(tok *lp, const char *fmt, u_int v, const char *sep)
{
	u_int		bit;
	int		len = 0;
	const char	*sepstr = "";

	for (; lp && lp->s; lp++) {
		for (bit = 1; bit != 0; bit <<= 1) {
			if (bit == lp->v) {
				len += snprintf(bittok2str_internal::buf + len,
				    256 - len, "%s%s", sepstr, lp->s);
				sepstr = sep;
				break;
			}
		}
	}
	if (len == 0)
		snprintf(bittok2str_internal::buf, 256, fmt ? fmt : "#%08x", v);
	return (bittok2str_internal::buf);
}