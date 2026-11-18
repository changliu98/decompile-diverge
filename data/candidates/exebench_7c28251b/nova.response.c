static __inline void
sun_gpstime2mjulianday(int line, double t, char **p)
{
	*p = (char *)g_scratch + (line * 7) + (t / (1.0 / 7));
}