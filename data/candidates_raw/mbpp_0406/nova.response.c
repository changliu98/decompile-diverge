static const NamedResource *
func0(unsigned int index)
{
	const NamedResource *drv;
	unsigned int i;

	i = index ^ (index >> 1);
	i ^= i >> 2;
	i ^= i >> 4;
	i ^= i >> 8;
	i ^= i >> 16;

	if (i & 1)
		drv = &g_usbs_odd_driver;
	else
		drv = &g_usbs_even_driver;

	return drv;
}