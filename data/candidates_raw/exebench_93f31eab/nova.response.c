static int func0(int *red, int *green, int *blue, void *data)
{
	float *color = data;
	*red   = (int)(color[0] * 255.0f / 3.0f);
	*green = (int)(color[1] * 255.0f / 3.0f);
	*blue  = (int)(color[2] * 255.0f / 3.0f);
	return 2;
}