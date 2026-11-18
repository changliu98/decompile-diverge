static int func0(unsigned char *arr, uint16_t val)
{
	int i, j;
	uint8_t x;

	if (!(val & 0x100)) {
		x = -1;
	} else {
		x = val & 0xff;
		arr[0] = 0;
		arr[1] = 1;
		for (i = 1, j = 2; j < 256; i <<= 1, j++) {
			if (i & 0x100) {
				i &= 0xff;
				i ^= x;
			}
			arr[j] = i;
		}
		x = 0;
	}

	return x;
}