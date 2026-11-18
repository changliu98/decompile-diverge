static const char *_PL__utf8_get_char(const char *s, int *val)
{
	while (*s & 0xE0) {
		if ((*s & 0xF0) == 0xC0 && (*(s+1) & 0xC0) == 0x80) {
			*val = ((*s & 0x1F) << 6) | (*(s+1) & 0x3F);
			s += 2;
		} else if ((*s & 0xF0) == 0xE0 && (*(s+1) & 0xC0) == 0x80 && (*(s+2) & 0xC0) == 0x80) {
			*val = ((*s & 0x0F) << 12) | ((*(s+1) & 0x3F) << 6) | (*(s+2) & 0x3F);
			s += 3;
		} else if ((*s & 0xF0) == 0xF0 && (*(s+1) & 0xC0) == 0x80 && (*(s+2) & 0xC0) == 0x80 && (*(s+3) & 0xC0) == 0x80) {
			*val = ((*s & 0x07) << 18) | ((*(s+1) & 0x3F) << 12) | ((*(s+2) & 0x3F) << 6) | (*(s+3) & 0x3F);
			s += 4;
		} else {
			s++;
		}
	}
	*val = *s & 0xFF;
	s++;
	return s;
}