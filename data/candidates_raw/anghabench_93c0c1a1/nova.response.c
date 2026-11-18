static unsigned int func0(unsigned short hue, unsigned char sat, unsigned char lum)
{
	unsigned char red, green, blue, h, i, f, p, q;

	h = hue / 360.0f * 360;
	i = (int)floor(h / 60);
	f = h / 60 - i;
	p = (unsigned char)(255 * (1 - f));
	q = (unsigned char)(255 * (1 - f * sat));

	switch (i) {
	case 0:
		red = q;
		green = p;
		blue = 0;
		break;
	case 1:
		red = p;
		green = q;
		blue = 0;
		break;
	case 2:
		red = 0;
		green = p;
		blue = q;
		break;
	case 3:
		red = 0;
		green = q;
		blue = p;
		break;
	case 4:
		red = q;
		green = 0;
		blue = p;
		break;
	case 5:
		red = p;
		green = 0;
		blue = q;
		break;
	}

	return (red << 16) | (green << 8) | blue;
}