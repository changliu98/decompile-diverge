__attribute__((used)) static int check_crc_flex(unsigned char *cp, int size)
{
	unsigned short crc = 0xffff;
	int result;

	if (size < 4) {
		result = -1;
		goto out;
	}

	while (size--)
		crc = (crc << 8) ^ crc_flex_table[((crc >> 8) ^ *cp++) & 0xff];

	if ((crc & 0xffff) != 0x7070) {
		result = -1;
		goto out;
	}

	result = 0;
out:
	return result;
}