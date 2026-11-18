unsigned short func0(const wchar_t *str, wchar_t *buf, unsigned int buf_size)
{
	unsigned int i = 0;
	const wchar_t *s = str;
	bool odd = false;

	if (buf_size > 0) {
		while (true) {
			if (*s == 0) {
				buf[i] = 0;
				break;
			}
			buf[i] = *s;
			s += 2;
			i++;
			if (i >= buf_size) {
				buf[i] = 0;
				break;
			}
		}
	} else {
		while (true) {
			if (*s == 0)
				break;
			odd =!odd;
			if (odd)
				s += 2;
		}
	}

	return i;
}