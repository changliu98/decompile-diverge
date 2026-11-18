static int func0(int src_val, int src_max, int dst_max)
{
	int dst_val;
	int scale_factor;

	if (src_max < dst_max)
		scale_factor = (src_max - 1) / dst_max;
	else
		scale_factor = dst_max;

	dst_val = (src_val * scale_factor) / src_max;
	return dst_val;
}