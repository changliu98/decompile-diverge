static int persistent_cache_read_entry_v3(struct tm *tm, struct tm *now, int *num)
{
	unsigned long t;
	struct tm *lt;
	int ret;
	static const int mdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	memset(tm, 0, sizeof(*tm));
	if (now == NULL)
		goto err;
	if (num == NULL)
		goto err;

	if (set_tm(tm, now, 12)!= 1)
		goto err;
	tm->tm_mon = now->tm_mon;
	tm->tm_mday = now->tm_mday;
	tm->tm_year = now->tm_year;

	t = (unsigned long)tm->tm_mon * 31 + (unsigned long)tm->tm_mday;
	if (t > (unsigned long)tm->tm_year * 365)
		goto err;
	tm->tm_isdst = -1;
	if (t > (unsigned long)tm->tm_year * 365 + is_leap(tm->tm_year))
		tm->tm_year++;
	tm->tm_yday = t;
	tm->tm_wday = tm->tm_year;
	lt = gmtime_r(&tm->tm_year, tm);
	if (lt == NULL)
		goto err;
	tm->tm_mon = lt->tm_mon;
	tm->tm_mday = lt->tm_mday;

	ret = set_tm(tm, tm, 12);
	if (ret!= 1)
		goto err;
	return 1;
err:
	return -1;
}