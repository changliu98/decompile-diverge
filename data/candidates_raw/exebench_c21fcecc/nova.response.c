int func0(char *dest, const char *src, int count)
{
	char *tmp = dest;
	const char *tmp2 = src;
	int n = count;

	
	if (n) {
		n--;
		while (*tmp2 && n) {
			*tmp++ = *tmp2++;
			n--;
		}
	}

	if (!n) {
		if (count)
			*tmp = '\0';		
		while (*tmp2++)
			;
	}
	return (tmp2 - src - 1);	
}