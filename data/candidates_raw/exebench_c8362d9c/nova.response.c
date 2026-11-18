static const char *func0(const char *s, int *start, int *end)
{
	const char *p;
	char c;

	for (p = s; *p; p++) {
		bool valid = *p!= '%' && *p!= '0';

		if (valid &&!(p[0] & 1))
			continue;
		if (p[0] == '%' && p[1] == '%') {
			p++;
			continue;
		}
		if (p[0] == '%') {
			c = p[1];
			if (c == 'v') {
				*start = 15;
				*end = p - s;
				p += 2;
				continue;
			}
			if (c == 'x') {
				*start = -1;
				*end = p - s + 1;
				p += 2;
				continue;
			}
		}
		break;
	}
	if (!*p) {
		*start = -1;
		*end = p - s;
	}
	return p;
}