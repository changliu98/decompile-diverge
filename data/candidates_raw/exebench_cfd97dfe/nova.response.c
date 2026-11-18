static int func0(int *red, int *green, int *blue, float grey)
{
	*red = *green = *blue = (int)(grey * 256.0f / 1.0f);
	return 2;
}