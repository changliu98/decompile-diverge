void insert_dle(unsigned char *dest, unsigned char *src, int count)
{
	while (--count) {
		*dest++ = *src;
		if (*src++ == DLE)
			*dest++ = DLE;
	}
}