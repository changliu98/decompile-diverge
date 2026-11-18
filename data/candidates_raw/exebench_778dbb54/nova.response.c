static int func0(int *red, int *green, int *blue, void *data)
{
	float f;

	f = (float)((unsigned long)data / 1000000.0f);

	f *= 256.0f / 60.0f;

	*red = (int)f;
	*green = (int)f % 256;

	return 2;
}