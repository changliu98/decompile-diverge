static int obdRevConvert_31(int *red, int *green, int *blue, void *data)
{
	unsigned i = (unsigned) data;
	*red   = (i / 256) % 256;
	*green = (i /   1) % 256;
	*blue  = (i / 256) % 256;
	return 2;
}