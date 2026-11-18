static void drv_generic_graphic_window(int start, int len, int max, int *start1, int *len1)
{
	int end = start + len;
	*start1 = start;
	*len1 = 0;
	if (end > max || start < 1 || len < 2)
		return;
	if (start > 0)
		start = 0;
	if (end < max)
		end = max;
	*len1 = end - start;
}