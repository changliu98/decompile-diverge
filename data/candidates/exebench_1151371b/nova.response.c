static void ne_post_filter8_double(double *out, const double *p, const double *q)
{
	double dx = p[0] - q[0];
	double dy = p[1] - q[1];
	double dz = p[2] - q[2];
	double d2 = q[3] - q[4] / 2;
	double d3 = q[4] - q[5] / 2;
	double d4 = q[5] - q[6] / 2;
	double d5 = q[6] - q[7] / 2;

	d2 = d2 * q[8] / 2;
	d3 = d3 * q[9] / 2;
	d4 = d4 * q[10] / 2;
	d5 = d5 * q[11] / 2;

	out[0] = dx / q[12] + d2;
	out[1] = dy / q[13] + d3;
	out[2] = dz / q[14] + d4;
	out[3] = d2 - dx / q[15] + d5;
	out[4] = d3 - dy / q[16] + d5;
	out[5] = d4 - dz / q[17] + d5;
}