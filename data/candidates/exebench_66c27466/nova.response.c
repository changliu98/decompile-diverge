static const char *sgml__utf8_get_char(const char *s, u64 *v)
{
	const char *p;

	
	if ((s[0] & 0xE0) == 0xC0 && (s[1] & 0xC0) == 0x80) {
		*v = ((u64)(s[0] & 0x1F) << 6) | (s[1] & 0x3F);
		p = s + 2;
		goto done;
	}

	
	if ((s[0] & 0xF0) == 0xE0 && (s[1] & 0xC0) == 0x80 &&
	    (s[2] & 0xC0) == 0x80) {
		*v = ((u64)(s[0] & 0x0F) << 12) |
			((u64)(s[1] & 0x3F) << 6) |
			(s[2] & 0x3F);
		p = s + 3;
		goto done;
	}

	
	if ((s[0] & 0xF8) == 0xF0 && (s[1] & 0xC0) == 0x80 &&
	    (s[2] & 0xC0) == 0x80 && (s[3] & 0xC0) == 0x80) {
		*v = ((u64)(s[0] & 0x07) << 18) |
			((u64)(s[1] & 0x3F) << 12) |
			((u64)(s[2] & 0x3F) << 6) |
			(s[3] & 0x3F);
		p = s + 4;
		goto done;
	}

	
	if ((s[0] & 0xFC) == 0xF8 && (s[1] & 0xC0) == 0x80 &&
	    (s[2] & 0xC0) == 0x80 && (s[3] &