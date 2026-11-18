static void func0(unsigned short *mask, unsigned short len)
{
	int i;

	for (i = 0; i < 14; i++, len >>= 1) {
		mask[i] = 0;
		if (len >= 1<<13) {
			mask[18] = 1;
			len -= 1<<13;
		}
		if (len >= 1<<12) {
			mask[16] = 1;
			len -= 1<<12;
		}
		if (len >= 1<<11) {
			mask[14] = 1;
			len -= 1<<11;
		}
		if (len >= 1<<10) {
			mask[12] = 1;
			len -= 1<<10;
		}
		if (len >= 1<<9) {
			mask[10] = 1;
			len -= 1<<9;
		}
		if (len >= 1<<8) {
			mask[8] = 1;
			len -= 1<<8;
		}
		if (len >= 1<<7) {
			mask[6] = 1;
			len -= 1<<7;
		}
		if (len >= 1<<6) {
			mask[4] = 1;
			len -= 1<<6;
		}
		if (len >= 1<<5) {
			mask[2] = 1;
			len -= 1<<5;
		}
		if (len >= 1<<4) {
			mask[0] = 1;
			len -= 1<<4;
		}
	}
}