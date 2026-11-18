int
filenvercmp(const char *a, ssize_t alen, const char *b, ssize_t blen)
{
	int			r;
	idx_t		a_plen,
				b_plen;
	bool		a_is_empty,
				b_is_empty,
				a_is_dot,
				b_is_dot,
				a_is_dotdot,
				b_is_dotdot;

	/*
	 * Handle empty strings and strings that are "." and ".."
	 */
	a_is_empty = alen < 0 ? a[0] == '\0' : alen == 0;
	b_is_empty = blen < 0 ? b[0] == '\0' : blen == 0;

	if (a_is_empty)
	{
		if (b_is_empty)
			return 0;
		else
			return -1;
	}
	else if (b_is_empty)
		return 1;

	a_is_dot = a[0] == '.';
	b_is_dot = b[0] == '.';

	if (a_is_dot && b_is_dot)
	{
		/*
		 * Both strings begin with a dot.  If they are the same length,
		 * then they are equal.  Otherwise, the one with the longer
		 * prefix is considered larger.
		 */
		a_is_dotdot = alen < 0 ? a[1] == '.' && a[2] == '\0' : alen == 2;
		b_is_dotdot = blen < 0 ? b[1] == '.' && b[2] == '\0' : blen == 2;

		if (a_is_dotdot)
		{
			if (b_is_dotdot)
				return 0;
			else
				return -1;
		}
		else if (b_is_dotdot)
			return 1;
	}
	else if (a_is_dot)
		return -1;
	else if (b_is_dot)
		return 1;

	/*
	 * Strip off any common prefixes.
	 */
	a_plen = file_prefixlen(a, &alen);
	b_plen = file_prefixlen(b, &blen);

	/*
	 * Do a version comparison on the strings without the common prefixes.
	 * If the prefixes are different lengths, then the string with the
	 * shorter prefix is considered smaller.
	 */
	a_is_empty = alen != a_plen;
	b_is_empty = blen != b_plen;

	r = verrevcmp(a, a_plen, b, b_plen);
	if (r == 0 && (a_is_empty || b_is_empty))
		r = verrevcmp(a, alen, b, blen);

	return r;
}