static char *
func0(uintmax_t x, char *s, int base)
{
	uintmax_t d;
	int n, c;

	n = 1;
	for (d = x << 1; d!= 0; d >>= 1)
		n++;
	for (; n-- > 0; s++) {
		c = x & 0x80? base - 1 : 0;
		x <<= 1;
		*s = c + (c < 10? '0' : (c < 37? 'A' : 'a') - 10);
	}
	return (s);
}