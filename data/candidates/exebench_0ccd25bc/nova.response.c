static int unicoder_utf32_decode(wchar_t *wc, const char *mb, unsigned n)
{
	int i, w, c;

	if (n == 2 || n == 1) {
		if (!mb)
			w = -1;
		else if (!wc)
			return -1;
		else {
			w = 0;
			for (i = 0; i < 4; i++) {
				if (n == 2) {
					if (i > 0)
						w = w << 8;
					w |= (unsigned char)mb[i];
				} else {
					if (i > 0)
						w = w >> 8;
					w |= (unsigned char)mb[i] << 24;
				}
			}
			if (w > 0x10ffff)
				w = -0x100000;
			else if (w > 0xfffff)
				w = -0x10000;
			*wc = w;
		}
		c = 4;
	} else
		c = -2;
	return c;
}