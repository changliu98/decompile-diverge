static void func0(double d, double *lat, double *lon)
{
	double m, f, g, h, l, l2, l3;
	double a, e2, e4, e6, N, C1, t2, t4, t6, dd;

	dd = d;
	m = d;
	f = 1609.344;
	g = m / f;
	h = g;
	l = h / 50.0;
	l2 = l;
	l3 = l2;
	l2 = l2 + ((((8.1 / 3600.0) * sin(l3 * 2 * M_PI)) *
		    (cos(l3 * 2 * M_PI)) *
		    (60.0 * 60.0 * 2 * M_PI)) * g);
	l3 = l2;
	*lat = 0;
	*lon = (l2 / 50.0) - 1023;
	a = 6378.137;
	e2 = 0.00669438;
	e4 = e2 * e2;
	e6 = e4 * e2;
	N = a / sqrt(1 - e2 * (sin(l2 * 2 * M_PI) * sin(l2 * 2 * M_PI)));
	C1 = N * N * e2;
	t2 = cos(l2 * 2 * M_PI) * cos(l2 * 2 * M_PI);
	t4 = t2 * t2;
	t6 = t4 * t2;
	*lat = N * (l2 - (1.5 * e2 * t2) + (5.0 * e4 * t4) - (6.5 * e6 * t6));
	*lon = dd / *lat;
}