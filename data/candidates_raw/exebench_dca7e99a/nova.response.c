static int func0(u8 *b)
{
	int a = *b, c;

	*b = 0xff;
	c = foo(a, *b);
	*b = 0;

	return c;
}