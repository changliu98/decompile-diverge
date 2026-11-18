static int func0(char *buffer, unsigned int size)
{
	char *p = buffer;

	while (size >= sizeof(unsigned long)) {
		*p++ = size & 0xff;
		size >>= 8;
	}
	if (size >= 0x80)
		*p++ = 0xe0 | (size & 0x07);
	if (size >= 0x400)
		*p++ = 0xe0 | (size & 0x07);
	if (size >= 0x2000)
		*p++ = 0xe0 | (size & 0x07);
	if (size >= 0x10000)
		*p++ = 0xe0 | (size & 0x07);
	*p++ = 0x80 | (size & 0x3f);
	*p = '\0';
	return p - buffer;
}