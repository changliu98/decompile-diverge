static void func0(int hh, int hh_end, int mm, int *mm_start, int *mm_end,
			int *ss_start, int *ss_end)
{
	int hh_start, hh_end_tmp;

	if (hh > hh_end)
		hh_end_tmp = hh;
	else
		hh_end_tmp = hh_end;

	hh_start = hh_end_tmp;

	while (1) {
		if (hh_start < hh_end) {
			if (hh_start == hh) {
				*ss_start = 0;
				*mm_start = 0;
				*ss_end = 0;
			} else if (hh_start == hh_end) {
				if (hh_end > hh)
					*ss_end = 60 - mm;
				else
					*ss_end = 60 + (600 * (hh_end - hh));
			} else if (hh_start == hh_end - 1) {
				if (hh_end > hh)
					*ss_end = 120 + (60 * (hh_end - hh));
				else
					*ss_end = 120 - (600 * (hh - hh_end));
			} else
				*ss_end = 240 + (60 * (hh_end - hh));
		} else {
			if (hh_end_tmp == hh_end) {
				*ss_end = 3600;
				*mm_end = 0;
			} else if (hh_end_tmp == hh_end - 1) {
				if (hh_end > hh)
					*ss_end = 3600 - (60 * (hh_end - hh));
				else
					*ss_end = 3600 + (600 * (hh - hh_end));
			} else
				*ss_end = 3600 + (60 * (hh_end - hh));
		}

		if (*ss_end <