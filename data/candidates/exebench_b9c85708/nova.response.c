static void easterj(int offset, int *day, int *month)
{
	int dd, mm, yy;

	dd = offset % 4;
	mm = offset % 7;
	yy = offset % 19;

	dd = (dd * 4 + mm * 2 + 15) % 30;
	mm = (dd + yy + 15) % 12;
	dd = (dd + yy + 15) % 30;

	*day = dd + 1;
	*month = mm + 1;
}