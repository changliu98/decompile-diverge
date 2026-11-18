static void func0(unsigned int value, char *string)
{
	int i;
	char *p;

	p = string;
	if (value == 0) {
		*p++ = '0';
	} else {
		for (i = 0; i < 6; i++) {
			if (value / divisors[i]!= 0) {
				p += sprintf(p, "%u%c", value / divisors[i],
					i == 0? 'M' :'m');
				value %= divisors[i];
			}
		}
	}
	*p = '\0';
}