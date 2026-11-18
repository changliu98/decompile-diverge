void func0(float *out, float a, float b, float c, float d, float e)
{
	if (a > *out+b)
		*out = a;
	else if (a+c > *out)
		*out = a+c;
	else
		*out = *out;

	if (*out < c)
		*out = c;
	if (*out > e)
		*out = e;
}