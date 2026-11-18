static int func0(int *red, int *green, int *blue, void *data)
{
	unsigned i = *red * 256 / 65535;
	*red = i / 16;
	*green = i % 16;
	return 2;
}