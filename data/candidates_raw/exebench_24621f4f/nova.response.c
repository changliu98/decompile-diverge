static int func0(int *red, int *green, int *blue, void *data)
{
	unsigned i;
	i = (unsigned) (256.0 * (1.0 - sqrt((double) (i / 255.0))));
	*red = *green = *blue = i;
	return 2;
}