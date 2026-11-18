static char *utf_16le_to_utf_8_truncated(const uint16_t *in, char *out, size_t in_len)
{
	char *p = out;
	uint16_t c;
	uint16_t d;

	if (!in_len) {
		p = out;
		goto out;
	}

	while (1) {
		c = *in++;
		if (!c)
			break;

		if (c >= 0xd800 && c < 0xe000) {
			d = *in++;
			if (!d)
				break;

			if (d >= 0xdc00 && d < 0xe000) {
				c = 0x10000 + ((c & 0x3ff) << 10) +
				    (d & 0x3ff);
			} else {
				c = 0xfffd;
				goto out;
			}
		}

		if (c >= 0xdc00 && c < 0xe000) {
			c = 0xfffd;
			goto out;
		}

		if (in_len < 2) {
			c = 0xfffd;
			goto out;
		}

		if (c >= 0x80 && c < 0x800) {
			*p++ = c;
			in_len--;
		} else if (c >= 0x800) {
			*p++ = 0xc0 | (c >> 12);
			*p++ = 0x80 | ((c >> 6) & 0x3f);
			*p++ = 0x80 | (c & 0x3f);
			in_len -= 3;
		} else {
			c = 0xfffd;
			goto out;
		}
	}
	*p = '\0';
	p = out;
out:
	return p;
}