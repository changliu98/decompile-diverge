static const char *
func0(int m, int n, int p)
{
	static char buf[10];
	int i;

	for (i = 0; ; i++) {
		if (i * m > p)
			break;
		if ((p - i * m) % n == 0) {
			sprintf(buf, "%d,%d", i, (p - i * m) / n);
			return (buf);
		}
	}
	return ("N/A");
}