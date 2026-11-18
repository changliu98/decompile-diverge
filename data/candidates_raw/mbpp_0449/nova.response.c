static struct s_srf_evc *func0(int m1, int e1, int m2, int e2, int m3,
    int e3)
{
	register int i;
	register struct s_srf_evc *evc;

	i = (m1 * 100000 + e1 * 1000 + m2 * 100 + e2 * 10 + m3) * (e3);
	if (!i)
		evc = &srf_evc_tab[0];
	else if (i < 0)
		evc = &srf_evc_tab[1];
	else
		evc = &srf_evc_tab[2];
	return evc;
}