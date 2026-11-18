static int cp_unfilter(int w, int h, int bpp, uint8_t* raw)
{
	int len = w * bpp;
	uint8_t *prev;
	int x;

	if (h > 0)
	{
#define FILTER_LOOP_FIRST(A) for (x = bpp; x < len; x++) raw[x] += A; break
		switch (*raw++)
		{
		case 0: break;
		case 1: FILTER_LOOP_FIRST(raw[x - bpp]);
		case 2: break;
		case 3: FILTER_LOOP_FIRST(raw[x - bpp] / 2);
		case 4: FILTER_LOOP_FIRST(cp_paeth(raw[x - bpp], 0, 0));
		default: return 0;
		}
#undef FILTER_LOOP_FIRST
	}

	prev = raw;
	raw += len;

	for (int y = 1; y < h; y++, prev = raw, raw += len)
	{
#define FILTER_LOOP(A, B) for (x = 0 ; x < bpp; x++) raw[x] += A; for (; x < len; x++) raw[x] += B; break
		switch (*raw++)
		{
		case 0: break;
		case 1: FILTER_LOOP(0          , raw[x - bpp] );
		case 2: FILTER_LOOP(prev[x]    , prev[x]);
		case 3: FILTER_LOOP(prev[x] / 2, (raw[x - bpp] + prev[x]) / 2);
		case 4: FILTER_LOOP(prev[x]    , cp_paeth(raw[x - bpp], prev[x], prev[x -bpp]));
		default: return 0;
		}
#undef FILTER_LOOP
	}

	return 1;
}