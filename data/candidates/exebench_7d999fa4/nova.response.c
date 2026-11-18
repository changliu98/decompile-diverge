static int bkm_scale(long *v, int mul)
{
	long tmp;
	int ret;

	tmp = *v * mul;
	if (tmp / mul!= *v)
		ret = 1;
	else {
		*v = tmp;
		ret = 0;
	}
	return ret;
}