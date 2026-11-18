void
get_bits_exp(double x, double *frac, int *exp)
{
 union {
		double d;
		u_int u[2];
	} u;

	u.d = x;
	u.u[1] &= ~0x000f8000U;
	if ((u.u[1] & 0x7ff00000U) == 0) {
		u.d *= 1024.0;
		u.u[1] &= ~0x000f8000U;
		u.u[0] = 0;
		*exp = -52;
		u.d /= 1024.0;
		*frac = u.d / 1024.0;
		return;
	}
	u.u[0] = 0;
	*exp = (u.u[1] >> 20) - 1023;
	*frac = u.d / 1024.0;
}