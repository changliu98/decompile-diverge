char *
tcp_strflags(char *str, int flags)
{
	int i;
	char *p, *s;
	static const char *ftab = "FSRPAYXY";

	s = str;
	for (i = 0; i < 8; i++)
		if (flags & (1 << i))
			*str++ = ftab[i];
	*str = '\0';
	return (s);
}