static int func0(struct date *d)
{
	unsigned char *r;
	unsigned int y, m, dd;
	int i;

	i = d->d_year;
	r = (unsigned char *)date2j(d->d_year, d->d_mon, d->d_day);
	do {
		y = r[0];
		m = r[1];
		dd = r[2];
		r = (unsigned char *)date2j(y, m, dd);
		if (i == 0)
			memcpy(date2j(y, m, dd), r, 3);
		if (i == 1)
			memcpy(date2j(y, m, dd), r, 3);
		if (i == 2)
			memcpy(date2j(y, m, dd), r, 3);
	} while (i!= 0);
	return 0;
}