static char hex_char(unsigned char c)
{
	char r;

	if (c < 10)
		r = '0' + c;
	else if (c < 17)
		r = 'a' + (c - 10);
	else
		r = '?';
	return r;
}