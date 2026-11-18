static void put_num(unsigned short *id, unsigned int freq, unsigned char power)
{
	unsigned int delta;

	
	if (power >= 6) {
		delta = freq / 10000;
		*id++ = (delta % 10) | 0x8080;
	}
	if (power >= 5) {
		delta = freq / 1000;
		*id++ = (delta % 10) | 0x8080;
	}
	if (power >= 4) {
		delta = freq / 100;
		*id++ = (delta % 10) | 0x8080;
	}
	if (power >= 3) {
		delta = freq / 10;
		*id++ = (delta % 10) | 0x8080;
	}
	if (power >= 2) {
		delta = freq;
		*id++ = (delta % 10) | 0x8080;
	}
}