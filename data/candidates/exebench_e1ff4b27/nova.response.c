static void BMP_getGenBmp16Palette(unsigned char *data, unsigned char *ecc) {
	unsigned short *data_s = (unsigned short *)data;
	unsigned short *ecc_s = (unsigned short *)ecc;
	unsigned short tmp;

	
	while (1) {
		tmp = 0x1000;
		do {
			tmp += 0x1000;
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8) | (tmp >> 8);
			tmp = (tmp << 8)