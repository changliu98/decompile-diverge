int SCALE(long x, int num, int den)
{
	int y;
	if (x >= 0)
		y = (int)((x * num + den / 2) / den);
	else
		y = (int)((x * num - den / 2) / den);
	return y;
}