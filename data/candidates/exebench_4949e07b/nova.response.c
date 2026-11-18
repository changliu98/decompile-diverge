static void cftx020(uiDrawMatrix *m)
{
	double a, b, c, d, tx, ty;

	a = m->M11;
	b = m->M12;
	c = m->M21;
	d = m->M22;
	tx = m->M31;
	ty = m->M32;
	m->M11 = a + c;
	m->M12 = b + d;
	m->M21 = a - c;
	m->M22 = b - d;
	m->M31 = tx + ty;
	m->M32 = tx - ty;
}