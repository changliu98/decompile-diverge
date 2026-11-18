static int func0(int src_val, int src_max, int dst_max)
{
	int dst_val;
	int scale_factor;

	if (src_max - 1 > dst_max)
		scale_factor = dst_max - 1;
	else
		scale_factor = src_max - 1;

	dst_val = (src_val * scale_factor) / src_max;

	return dst_val;
}