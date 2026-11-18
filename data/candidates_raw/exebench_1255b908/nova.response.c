static int func0(int *a, int *b, int min, int max)
{
	int ret;

	if (*a < min) {
		ret = min - *a;
		*b += *a;
		*a = min;
	} else if (*a + *b < max) {
		*b += *a;
	} else {
		ret = *a + *b - max;
		*a = max;
		*b -= ret;
	}
	return ret;
}