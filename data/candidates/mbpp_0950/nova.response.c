static const char *func0(int year)
{
	const char *months[] = {
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
	};

	int mon = (year - 2000) % 12;
	if (mon < 0)
		mon += 12;

	
	return months[mon];
}