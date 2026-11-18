static unsigned int func0(const unsigned char *data, size_t size, unsigned int crc)
{
	const unsigned char *last;

	for (last = data; size > 0; size--, data++) {
		unsigned int i;

		crc ^= *data;

		for (i = 0; i < 8; i++) {
			if (crc & 0x01) {
				crc >>= 1;
				crc ^= 0xedb88320UL;
			} else {
				crc >>= 1;
			}
		}
	}

	return crc;
}