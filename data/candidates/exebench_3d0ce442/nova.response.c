float
add_denormal_prevention_white_noise(unsigned int *x)
{
	union {float f; uint32_t i;} u;

	*x = *x * 1234567 + 890123;
	u.i = (*x & 0xffff) | 0x7f000000;
	return (u.f);
}