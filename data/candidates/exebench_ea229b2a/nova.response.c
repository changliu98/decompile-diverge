static const char *convert_set_sign(const char *strp, int *sign)
{
	*sign = 1;
	if (strp) {
		if (*strp == '+') {
			*sign = 1;
			strp++;
		} else if (*strp == '-') {
			*sign = -1;
			strp++;
		}
	}
	return strp;
}