void func0(double out[6], const double m[6], const double n[6])
{
	double det_m = m[0] * m[3] - m[1] * m[2];
	double det_n = n[0] * n[3] - n[1] * n[2];
	out[0] = (m[3] * det_n - n[3] * det_m) / det_m;
	out[1] = (n[2] * det_m - m[2] * det_n) / det_m;
	out[2] = (m[1] * det_n - n[1] * det_m) / det_m;
	out[3] = (n[0] * det_m - m[0] * det_n) / det_m;
	out[4] = (m[4] * n[3] - n[4] * m[3]) / det_m;
	out[5] = (n[4] * m[0] - m[4] * n[0]) / det_m;
}