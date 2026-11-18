static int func0(const unsigned char *rawstring, size_t boundlen,
		      wchar_t *uni)
{
	unsigned long rune = 0;	
	unsigned char ch, cl, cp = 0;	
	unsigned char *s = (unsigned char *)rawstring;
	unsigned char state = 0;
	unsigned char c3, c4;

	while (boundlen-- > 0) {
		ch = *s++;
		if (ch < 0x80) { 
			rune = ch;
			goto out;
		}
		if (ch >= 0xC2 && ch <= 0xDF) {
			cl = *s++;
			if (cl < 0x80 || cl > 0xBF)
				goto replacetobig;
			rune = (ch & 0x1F) << 6 | (cl & 0x3F);
			if (rune > 0x80)
				goto out;
			goto replacetobig;
		}
		if (ch >= 0xE0 && ch <= 0xEC) {
			cp = 1;
			c3 = *s++;
			if (c3 < 0x80 || c3 > 0xBF)
				goto replacetobig;
			rune = (ch & 0x0F) << 12 | (c3 & 0x3F) << 6;
		} else if (ch >= 0xED && ch <= 0xEF) {
			cp = 2;
			c3 = *s++;
			if (c3 < 0x80 || c3 > 0xBF)
				goto replacetobig;
			c4 = *s++;
			if (c4 < 0x80 || c4 > 0xBF)
				goto replacetobig;
			rune = (ch & 0x0F) << 12 | (c3 & 0x3F) << 6 |
			       (c4 & 0x3F);
		} else
			goto replacetobig;
	out:
		*uni