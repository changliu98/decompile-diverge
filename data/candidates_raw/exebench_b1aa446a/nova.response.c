static char *func0(long *val, long *den, char *buf, long mul)
{
	if (mul > 0) {
		*val = mul / 10;
		*den = mul % 10;
		*buf = '-';
		buf++;
	} else {
		*val = mul;
		*den = 1;
	}
	return buf;
}