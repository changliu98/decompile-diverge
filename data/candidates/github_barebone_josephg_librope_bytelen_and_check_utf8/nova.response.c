size_t bytelen_and_check_utf8(const char *s)
{
	const char *p = s;
	size_t len;
	size_t ret;

	for (;;) {
		unsigned char c = *p;
		size_t n;

		if (!c)
			break;

		n = utf8_char_length(c);
		if (n == (size_t)-1) {
			ret = -1;
			goto out;
		}

		p++;
		n--;

		while (n > 0) {
			if ((*p & 0xc0)!= 0x80) {
				ret = -1;
				goto out;
			}
			p++;
			n--;
		}
	}

	ret = p - s;
out:
	len = ret;
	return ret;
}