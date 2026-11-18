static void func0(float f, int *mantissa, int *exponent)
{
	union {float f; uint32_t i;} u = {f};
	*mantissa = (u.i & 0x1fffff) | 0x800000;
	*exponent = ((u.i & 0x7f800000) >> 23) - 127;
	if (u.i & 0x80000000) *mantissa = -*mantissa;
}