static void func0(long year, int *y, int *m, int *d)
{
	long mjd, jd, l, n;

	
	if (year < 1 || year > 4999) {
		*y = 0;
		*m = 0;
		*d = 0;
		return;
	}

	
	mjd = year * 365L + 1721119L;

	
	jd = mjd + 365L * (year - 1) / 400L - 365L * (year - 1) / 100L
		+ 365L * (year - 1) / 4L;

	
	l = jd + 68572L;
	n = 4 * l / 146097L;
	l = l - (146097L * n + 3) / 4;

	
	jdn = l;
	jdm = (4 * l + 3) / 1461L;
	jdd = l / 4;

	
	if (jdm < 10) {
		jdm += 3;
	} else {
		jdn += 1;
		jdm -= 9;
	}

	
	jdn += 4294967;
	if (jdn <= 0)
		jdn -= 1;

	*y = jdn;
	*m = jdm;
	*d = jdd;
}