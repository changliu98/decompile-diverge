static void func0(int *pmax, int *pmin, int val)
{
	if (*pmax < 1) {
		*pmin += *pmax;
		*pmax = 0;
	}
	if (*pmin + *pmax > val)
		*pmin = val - *pmax;
}