static double
frexp(double x, int *expt)
{
	double fp;
	int expn;

	expn = 0;
	fp = x;
	if (fp < 0) {
		fp = -fp;
		expn = -2046;
	}
	if (fp >= 1) {
		while (fp >= 10) {
			fp /= 10;
			expn++;
		}
	} else {
		while (fp < 0.1) {
			fp *= 10;
			expn--;
		}
	}
	*expt = expn + 2046;
	return (fp * 2048);
}