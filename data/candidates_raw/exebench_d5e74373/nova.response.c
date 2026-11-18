static int func0(int *red, int *green, int *blue, float temperature)
{
	
	float t = temperature + 60;
	*red = (int)(t * (255.0f / 120.0f));
	*green = (int)(t * (255.0f / 70.0f));
	*blue = 256 - *red;
	return 2;
}