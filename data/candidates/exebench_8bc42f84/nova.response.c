static void mpeg3video_calc_mv(u32 *n, int bits, int up, int down, int carry)
{
	int lim = (1 << bits) / 2;
	int rem = *n;

	if (carry)
		rem >>= 1;

	rem += up + (1 << bits) - down;

	if (rem >= lim) {
		rem -= lim;
		if (rem >= lim)
			rem -= lim;
	} else if (rem >= -lim) {
		rem -= -lim;
		if (rem >= -lim)
			rem -= -lim;
	}

	if (carry)
		rem <<= 1;

	*n = rem;
}