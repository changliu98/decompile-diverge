void
insert_dle(unsigned char *dest, unsigned char *src, int count) {
	/* <DLE> in input stream have to be flagged as <DLE><DLE> */
	while (count--) {
		*dest++ = *src;
		if (*src++ == DLE)
			*dest++ = DLE;
	}
}