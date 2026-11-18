static void func0(unsigned int *crc, unsigned char db)
{
	int i;

	for (i = 0; i < 8; i++) {
		*crc <<= 1;
		if ((db ^ (*crc & 0x100))!= 0)
			*crc ^= 0x107;
		db >>= 1;
	}
	*crc &= 0xffff;
}