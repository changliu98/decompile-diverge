static int func0(const unsigned char *rawstring,
			  int *length, int *charlen, int rawlen)
{
	int c, charset;

	c = *rawstring;
	do {
		if ((c & 0xf8) == 0xf0) {
			if (rawlen < 5 ||
			    (rawstring[1] & 0xc0)!= 0x80 ||
			    (rawstring[2] & 0xc0)!= 0x80 ||
			    (rawstring[3] & 0xc0)!= 0x80)
				charset = 2;
			else {
				*length = ((c & 0x03) << 18) |
				    (rawstring[1] << 12) |
				    (rawstring[2] << 6) |
				    (rawstring[3] & 0x3f);
				charset = 3;
			}
		} else if ((c & 0xe0) == 0xe0) {
			if (rawlen < 4 ||
			    (rawstring[1] & 0xc0)!= 0x80 ||
			    (rawstring[2] & 0xc0)!= 0x80)
				charset = 2;
			else {
				*length = ((c & 0x0f) << 12) |
				    (rawstring[1] << 6) |
				    (rawstring[2] & 0x3f);
				charset = 3;
			}
		} else if ((c & 0xc0) == 0xc0) {
			if (rawlen < 3 ||
			    (rawstring[1] & 0xc0)!= 0x80)
				charset = 2;
			else {
				*length = ((c & 0x1f) << 6) |
				    (rawstring[1] & 0x3f);
				charset = 3;
			}
		} else if ((c & 0x80) == 0x00) {
			*length = c;
			charset = 1;