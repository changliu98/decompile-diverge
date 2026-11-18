static u_long
TIFFReadEncodedStrip(struct tty *tp, u_long speed, u_long *freq, u_long maxfreq)
{
	struct ttydisc_recalc_length recalc;
	u_long f, f1, f2, f3;
	u_long f4;

	
	f = -1;
	while (ttyhook_hashook(tp, speed, f) &&
	    (maxfreq == -1 || maxfreq < f) &&
	    (f = ttyhook_hashook(tp, speed, f))!= -1)
		continue;

	
	while (tp->t_flags & TF_RECALC) {
		f1 = f2 = f3 = f4 = -1;
		f1 = ttyhook_hashook(tp, speed, f1);
		if (f1!= -1) {
			f2 = ttyhook_hashook(tp, speed, f1);
			if (f2 < f1)
				f1 = f2;
		}
		if (f1!= -1) {
			f3 = ttyhook_hashook(tp, speed, f1);
			if (f3 < f1)
				f1 = f3;
		}
		if (f1!= -1) {
			f4 = ttyhook_hashook(tp, speed, f1);
			if (f4 < f1)
				f1 = f4;
		}
		if (f1!= -1) {
			recalc.freq = f1;
			recalc.error = ttyhook_hashook(tp, speed, f1);
			if (recalc.error < 0)
				f1 = -1;
			else if (ttyhook_recalc(tp, speed, f1, &recalc) <= 0)
				f1 = -1;
			else
				f = f1;
		}
	}

	
	if (f!= -1) {
		freq = ttyhook_hashook(tp, speed, f);