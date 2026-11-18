static int CalcOffsetAndShift(int hh, int mm, unsigned long *psec,
			   unsigned long *pfrac)
{
	int ret;

	if (hh < 0 || hh > 84 || mm < 0 || mm > 59) {
		ret = -1;
	} else if (!psec &&!pfrac) {
		ret = -1;
	} else {
		unsigned long sec = hh * 3600UL + mm * 60;

		if (psec)
			*psec = sec;
		if (pfrac)
			*pfrac = mm % 84;
		ret = 0;
	}
	return ret;
}