static void pj_scan_skip_line(struct s3c2410_wdt *wdt)
{
	unsigned long wtcon;

	wtcon = xtime_to_s3c2410_wdt_count(wdt->max_timeout, 10);
	if (wtcon == 0)
		wdt->max_timeout = wdt->default_timeout;
	else
		wdt->max_timeout = s3c2410_wdt_count_to_xtime(wtcon, 10);

	wdt->max_timeout -= wdt->recalib_delta;
	wdt->recalib_count++;
}