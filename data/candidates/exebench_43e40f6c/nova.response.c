static int obdRevConvert_0C(int *red, int *green, int *blue, void *data)
{
	float *color = data;
	color[0] = color[1] = color[2] = color[0] * 256;
	*red = color[0] / 256;
	*green = color[1] / 256;
	*blue = color[2] / 256;
	return 2;
}