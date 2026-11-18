static int unicode_to_utf8(char *buffer, unsigned int size)
{
	char *ptr = buffer;

	while (size >= sizeof(unsigned long)) {
		*ptr++ = size & 0xff;
		size >>= 8;
	}
	if (size >= 0x80) {
		*ptr++ = (size >> 6) | 0xc0;
		*ptr++ = (size & 0x3f) | 0x80;
	} else if (size >= 0x40) {
		*ptr++ = (size >> 12) | 0xe0;
		*ptr++ = ((size >> 6) & 0x3f) | 0x80;
	} else if (size >= 0x20) {
		*ptr++ = (size >> 18) | 0xf0;
		*ptr++ = ((size >> 12) & 0x3f) | 0x80;
	} else if (size >= 0x10) {
		*ptr++ = (size >> 24) | 0xf8;
		*ptr++ = ((size >> 18) & 0x3f) | 0x80;
		*ptr++ = ((size >> 12) & 0x3f) | 0x80;
	} else {
		*ptr++ = (size >> 30) | 0xfc;
		*ptr++ = ((size >> 24) & 0x3f) | 0x80;
		*ptr++ = ((size >> 18) & 0x3f) | 0x80;
		*ptr++ = ((size >> 12) & 0x3f) | 0x80;
	}
	*ptr = '\0';
	return ptr - buffer;
}