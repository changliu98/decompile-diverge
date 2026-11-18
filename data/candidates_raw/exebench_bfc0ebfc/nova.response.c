static void func0(unsigned int c, char *s)
{
	if (!s)
		return;
	s[0] = s[1] = s[2] = 0;
	if (c < 0x80)
		s[0] = c;
	else if (c < 0x800) {
		s[0] = ((c >> 6) & 0x1F) | 0xC0;
		s[1] = (c & 0x3F) | 0x80;
	} else if (c < 0x10000) {
		s[0] = (((c >> 12) & 0x0F) | 0xE0);
		s[1] = (((c >> 6) & 0x3F) | 0x80);
		s[2] = (c & 0x3F) | 0x80;
	} else if (c < 0x200000) {
		s[0] = (((c >> 18) & 0x07) | 0xF0);
		s[1] = (((c >> 12) & 0x3F) | 0x80);
		s[2] = (((c >> 6) & 0x3F) | 0x80);
		s[3] = (c & 0x3F) | 0x80;
	}
}