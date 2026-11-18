static const char *func0(const char *s, unsigned char from, unsigned char to, size_t *len)
{
	const char *p, *q;
	size_t l;
	unsigned char c;
	unsigned long long b;

	while (1) {
		p = s;
		b = *len;
		while (b >= 9 && (p = memchr(p, from, b))!= NULL) {
			q = p;
			while (b >= 9 && (c = *q) == from) {
				q++;
				b--;
			}
			b &= ~7;
			if (((unsigned long long) p & 7) == 0) {
				do {
					p += 8;
					b -= 8;
					if (((unsigned long long) p & 7) == 0) {
						do {
							p += 8;
							b -= 8;
						} while (b >= 9 && *p == from);
						b &= ~7;
					}
				} while (b >= 9 && *p == to);
				b &= ~7;
				if (((unsigned long long) p & 7) == 0) {
					do {
						p += 8;
						b -= 8;
					} while (b >= 9 && *p == to);
					b &= ~7;
					if (((unsigned long long) p & 7) == 0) {
						do {
							p += 8;
							b -= 8;
						} while (b >= 9 && *p == to);
						b &= ~7;
					}
				}
			}
			l = q - p;
			if (l & 7) {
				do {
					if (*q == to) {
						q++;
						break;
					}
					q++;
					b--;
				} while (b >= 9);
				b &= ~7;
				if (((unsigned long long) q & 7) == 0) {
					do {
						q +=