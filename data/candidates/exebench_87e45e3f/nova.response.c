static void encode_int(char *s, int n)
{
	int i, j, k;

	i = 0;
	if (n > 0) {
		if (n & 0x7000) {
			*s++ = '@' + ((n >> 10) & 0x1f);
			i++;
		}
		if (n & 0x03e0) {
			*s++ = '!' + ((n >> 4) & 0x3f);
			i++;
		}
	} else {
		n = -n;
		n &= 0x0f;
		i = 1;
	}
	if (n & 0x0f)
		*s++ ='' + (0x10 | (n & 0x0f));
	else
		*s++ ='';
	if (!i)
		*s++ ='' + 0x10;
	*s++ = 0;
}