static int setsize(unsigned long rate,
				   unsigned int *ndiv,
				   unsigned int *fdiv1,
				   unsigned int *fdiv2)
{
	unsigned long bestrate = 0;
	unsigned long tmp;
	unsigned int n, f1, f2;
	int ret = -1;

	
	for (n = 1; n <= 1024; n++) {
		f1 = 62;
		f2 = 0;
		tmp = rate * f1 / n;
		if (rate % tmp)
			tmp++;
		if (tmp > bestrate)
			continue;
		bestrate = tmp;
		f1 = rate / tmp;
		if (rate % f1) {
			f2++;
			f1++;
			tmp = rate * f1 / n;
			if (rate % tmp)
				tmp++;
		}
		if (tmp > bestrate)
			continue;
		bestrate = tmp;
		ret = 0;
	}

	*ndiv = n;
	*fdiv1 = f1;
	*fdiv2 = f2;

	return ret;
}