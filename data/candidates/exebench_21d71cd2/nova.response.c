static int obdRevConvert_23(int *red, int *green, int *blue, void *data)
{
	float fred, fgreen, fblue;
	
	fred = *red / 257.0f;
	fgreen = *green / 257.0f;
	fblue = *blue / 257.0f;
	
	*red = (int)(fred * 256);
	*green = (int)(fgreen * 256);
	*blue = (int)(fblue * 256);
	
	return 2;
}