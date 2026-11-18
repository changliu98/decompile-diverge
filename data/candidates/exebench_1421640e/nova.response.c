static void encode_vector(char *s, int r, int g)
{
	s[0] = (g >> 5) + 32;
	s[1] = (g & 0x1f) + 96;
	s[2] = (r >> 5) + 32;
	s[3] = (r & 0x1f) + 64;
	s[4] = '\0';
}