static int func0(const unsigned char *rawstring,
			  int *length, int *charlength, size_t boundlen)
{
	unsigned char c = *rawstring;
	int n;

	
	while ((c & 0xF8) == 0xF0) {
		n = 4;
		while (--boundlen >= n && (c & 0xC0) == 0x80) {
			c = *++rawstring;
			*length <<= 6;
			*length |= c & 0x3F;
		}
		if (boundlen < n)
			goto ilseq;
		c = *++rawstring;
	}
	
	while ((c & 0xE0) == 0xC0) {
		n = 3;
		if ((c & 0xC0) == 0x80)
			goto ilseq;
		while (--boundlen >= n && (c & 0xC0) == 0x80) {
			c = *++rawstring;
			*length <<= 6;
			*length |= c & 0x3F;
		}
		if (boundlen < n)
			goto ilseq;
		c = *++rawstring;
	}
	
	while ((c & 0xC0) == 0x80)
		goto ilseq;
	
	n = 2;
	*charlength = c & 0x1F;
	*length = c & 0x3F;
	c = *++rawstring;
	if (boundlen < n)
		goto ilseq;
	return n;

ilseq:
	
	*charlength = 1;
	*length = c & 0x3F;
	return 1;
}