static void func0(unsigned long *x, unsigned long y, unsigned long m)
{
	*x = (*x * 25173) + 13849;
	*x = (*x % (m - y)) + y;
}