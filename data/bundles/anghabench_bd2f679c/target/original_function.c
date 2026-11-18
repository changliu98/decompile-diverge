void crc8_byte(unsigned int *crc, unsigned char db)
{
	int i,f;

	for(i=0;i<8;i++) {
		f = (*crc ^ db) & 1;
		*crc >>= 1;
		db >>= 1;
		if(f)
			*crc ^= 0x8c;
	}
	*crc &= 0xff;
}